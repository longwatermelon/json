#include "../include/parser.h"


json::utils::Parser::Parser(const std::string& contents)
{
	lexer = Lexer(contents);
	current_token = lexer.next_token();
}


void json::utils::Parser::eat(TokenType type)
{
	if (current_token.type != type)
	{
		std::stringstream ss;
		ss << "unexpected token '" << current_token.value << "' at line " << lexer.nline << "\n";
		throw std::runtime_error(ss.str());
	}

	current_token = lexer.next_token();
}


void json::utils::Parser::parse()
{
	eat(TokenType::TOKEN_LBRACE);

	std::unique_ptr<Node> pair = parse_pair();
	map[pair->pair_first] = std::move(pair->pair_second);

	while (lexer.index < lexer.contents.size())
	{
		pair = parse_pair();

		if (!pair) break;
		
		map[pair->pair_first] = std::move(pair->pair_second);
	}
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_expr()
{
	switch (current_token.type)
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

	pair->pair_first = key->string_value;
	pair->pair_second = std::move(value);

	if (current_token.type != TokenType::TOKEN_COMMA)
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
	std::unique_ptr<Node> key = std::make_unique<Node>(NodeType::NODE_STRING);

	key->string_value = current_token.value;

	eat(TokenType::TOKEN_STRING);
	return key;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_value()
{
	return parse_expr();
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_int()
{
	std::unique_ptr<Node> node_int = std::make_unique<Node>(NodeType::NODE_INT);
	std::stringstream(current_token.value) >> node_int->int_value;
	eat(TokenType::TOKEN_INT);

	return node_int;
}


std::unique_ptr<json::utils::Node> json::utils::Parser::parse_string()
{
	std::unique_ptr<Node> node_str = std::make_unique<Node>(NodeType::NODE_STRING);
	node_str->string_value = current_token.value;
	eat(TokenType::TOKEN_STRING);

	return node_str;
}