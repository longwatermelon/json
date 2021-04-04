#include "../include/lexer.h"


json::utils::Lexer::Lexer(const std::string& contents)
	: contents(contents)
{
	if (contents.empty())
	{
		throw std::runtime_error("cant read file: file is either empty or doesnt exist\n");
	}

	current_char = contents[index];
}


json::utils::Token json::utils::Lexer::next_token()
{
	while (index < contents.size())
	{
		while (isspace(current_char) && current_char != '\n')
		{
			advance();
		}

		if (isdigit(current_char))
		{
			return Token(TokenType::TOKEN_INT, collect_int());
		}

		switch (current_char)
		{
		case ',': advance(); return Token(TokenType::TOKEN_COMMA, std::string(1, contents[index - 1]));
		case ':': advance(); return Token(TokenType::TOKEN_COLON, std::string(1, contents[index - 1]));
		case '{': advance(); return Token(TokenType::TOKEN_LBRACE, std::string(1, contents[index - 1]));
		case '}': advance(); return Token(TokenType::TOKEN_RBRACE, std::string(1, contents[index - 1]));
		case '"': return Token(TokenType::TOKEN_STRING, collect_string());
		case '.': advance(); return Token(TokenType::TOKEN_PERIOD, std::string(1, contents[index - 1]));
		case '[': advance(); return Token(TokenType::TOKEN_LBRACKET, std::string(1, contents[index - 1]));
		case ']': advance(); return Token(TokenType::TOKEN_RBRACKET, std::string(1, contents[index - 1]));
		}

		advance();
		++nline;
	}

	return Token(TokenType::TOKEN_EOF, "");
}


void json::utils::Lexer::advance()
{
	if (++index < contents.size())
	{
		current_char = contents[index];
	}
}


std::string json::utils::Lexer::collect_string()
{
	std::string str;
	advance();

	while (current_char != '"' && index < contents.size() && current_char != '\n')
	{
		str += current_char;
		advance();
	}

	advance();
	return str;
}


std::string json::utils::Lexer::collect_int()
{
	std::string integer;
	advance();

	while (isdigit(current_char) && index < contents.size() && current_char != '\n')
	{
		integer += current_char;
		advance();
	}

	advance();
	return integer;
}