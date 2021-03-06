#include "../include/parser.h"
#include "../include/utils.h"


json::utils::Parser::Parser(const std::string& contents)
{
	m_lexer = Lexer(contents);
	m_current_token = m_lexer.next_token();
}


void json::utils::Parser::eat(TokenType type)
{
	if (m_current_token.type != type)
	{
		std::stringstream ss;
		ss << "unexpected token '" << m_current_token.value << "' at line " << m_lexer.m_nline << "\n";
		throw std::runtime_error(ss.str());
	}

	m_current_token = m_lexer.next_token();
}


void json::utils::Parser::parse()
{
	if (m_current_token.type == TokenType::TOKEN_LBRACE)
	{
		eat(TokenType::TOKEN_LBRACE);

		std::unique_ptr<Node> pair = parse_pair();
		m_map[pair->pair_first] = std::move(pair->pair_second);

		while (m_lexer.m_index < m_lexer.m_contents.size())
		{
			pair = parse_pair();

			if (!pair) break;

			m_map[pair->pair_first] = std::move(pair->pair_second);
		}
	}
	else
	{
		std::unique_ptr<Node> list = parse_list();

		vector vec = std::get<vector>(list->literal_value);

		for (int i = 0; i < vec.get().size(); ++i)
		{
			m_list.emplace_back(vec[i]);
		}
	}
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_expr()
{
	switch (m_current_token.type)
	{
	case TokenType::TOKEN_INT: return parse_int();
	case TokenType::TOKEN_STRING: return parse_string();
	case TokenType::TOKEN_LBRACKET: return parse_list();
	}

	return nullptr;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_pair()
{
	std::unique_ptr<Node> pair = std::make_unique<Node>(NodeType::NODE_PAIR);

	std::unique_ptr<Node> key = parse_key();
	eat(TokenType::TOKEN_COLON);
	std::unique_ptr<Node> value = parse_value();

	pair->pair_first = std::get<std::string>(key->literal_value);
	pair->pair_second = std::move(value);

	if (m_current_token.type != TokenType::TOKEN_COMMA)
	{
		eat(TokenType::TOKEN_RBRACE);
	}
	else
	{
		eat(TokenType::TOKEN_COMMA);
	}

	return pair;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_key()
{
	std::unique_ptr<Node> key = std::make_unique<Node>(NodeType::NODE_LITERAL);

	key->literal_value = m_current_token.value;

	eat(TokenType::TOKEN_STRING);
	return key;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_value()
{
	return parse_expr();
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_int()
{
	std::unique_ptr<Node> node_int = std::make_unique<Node>(NodeType::NODE_LITERAL);
	node_int->literal_value = m_current_token.value;
	node_int->literal_value = std::stoi(std::get<std::string>(node_int->literal_value));
	node_int->literal_type = LiteralType::INT;
	eat(TokenType::TOKEN_INT);

	return node_int;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_string()
{
	std::unique_ptr<Node> node_str = std::make_unique<Node>(NodeType::NODE_LITERAL);
	node_str->literal_value = m_current_token.value;
	node_str->literal_type = LiteralType::STRING;
	eat(TokenType::TOKEN_STRING);

	return node_str;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_list()
{
	std::unique_ptr<Node> list = std::make_unique<Node>(NodeType::NODE_LITERAL);
	list->literal_type = LiteralType::LIST;
	list->literal_value = vector();

	eat(TokenType::TOKEN_LBRACKET);

	vector& vec = std::get<vector>(list->literal_value);

	while (m_current_token.type != TokenType::TOKEN_RBRACKET)
	{
		switch (m_current_token.type)
		{
		case TokenType::TOKEN_INT: vec.append(std::stoi(m_current_token.value)); break;
		default: vec.append(m_current_token.value); break;
		}

		eat(m_current_token.type);

		if (m_current_token.type == TokenType::TOKEN_RBRACKET) break;
		else eat(TokenType::TOKEN_COMMA);
	}

	eat(TokenType::TOKEN_RBRACKET);

	return list;
}