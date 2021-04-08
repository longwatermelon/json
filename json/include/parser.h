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
		Lexer m_lexer;
		Token m_current_token;

		std::map<std::string, std::unique_ptr<Node>> m_map;
		std::vector<json_variant> m_list;

		Parser(const std::string& contents);

		void eat(TokenType type);

		void parse();
		std::unique_ptr<Node> parse_expr();

		std::unique_ptr<Node> parse_pair();
		std::unique_ptr<Node> parse_key();
		std::unique_ptr<Node> parse_value();

		std::unique_ptr<Node> parse_int();
		std::unique_ptr<Node> parse_string();
		std::unique_ptr<Node> parse_list();
	};
}