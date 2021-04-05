#pragma once
#include "token.h"
#include <iostream>
#include <sstream>


namespace json::utils
{
	class Lexer
	{
	public:
		std::string contents;

		size_t index{ 0 };
		char current_char{ ' ' };

		size_t nline{ 0 };

		Lexer() = default;

		Lexer(const std::string& contents);

		Token next_token();

		void advance();

		std::string collect_string();
		std::string collect_int();
	};
}