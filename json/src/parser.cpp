#include "../include/parser.h"


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


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_expr()
{
	switch (m_current_token.type)
	{
	case TokenType::TOKEN_INT: return parse_int();
	case TokenType::TOKEN_STRING: return parse_string();
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