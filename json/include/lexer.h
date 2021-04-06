#pragma once
#include "token.h"
#include <iostream>
#include <sstream>


namespace json::utils
{
	class Lexer
	{
	public:
		std::string m_contents;

		size_t m_index{ 0 };
		char m_current_char{ ' ' };

		size_t m_nline{ 0 };

		Lexer() = default;

		Lexer(const std::string& contents);

		Token next_token();

		void advance();

		std::string collect_string();
		std::string collect_int();
	};
}