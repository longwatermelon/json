#pragma once
#include "lexer.h"
#include "node.h"
#include <map>
#include <variant>


namespace json::utils
{
	class Parser
	{
	public:
		Lexer lexer;
		Token current_token;

		std::map<std::string, std::unique_ptr<Node>> map;

		Parser(const std::string& contents);

		void eat(TokenType type);

		void parse();
		std::unique_ptr<Node> parse_expr();

		std::unique_ptr<Node> parse_pair();
		std::unique_ptr<Node> parse_key();
		std::unique_ptr<Node> parse_value();

		std::unique_ptr<Node> parse_int();
		std::unique_ptr<Node> parse_string();
	};
}