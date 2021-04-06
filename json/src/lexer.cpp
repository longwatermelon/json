#include "../include/lexer.h"


json::utils::Lexer::Lexer(const std::string& contents)
	: m_contents(contents)
{
	if (contents.empty())
	{
		throw std::runtime_error("cant read file: file is either empty or doesnt exist\n");
	}

	m_current_char = contents[m_index];
}


json::utils::Token json::utils::Lexer::next_token()
{
	while (m_index < m_contents.size())
	{
		while (isspace(m_current_char) && m_current_char != '\n')
		{
			advance();
		}

		if (isdigit(m_current_char))
		{
			return Token(TokenType::TOKEN_INT, collect_int());
		}

		switch (m_current_char)
		{
		case ',': advance(); return Token(TokenType::TOKEN_COMMA, std::string(1, m_contents[m_index - 1]));
		case ':': advance(); return Token(TokenType::TOKEN_COLON, std::string(1, m_contents[m_index - 1]));
		case '{': advance(); return Token(TokenType::TOKEN_LBRACE, std::string(1, m_contents[m_index - 1]));
		case '}': advance(); return Token(TokenType::TOKEN_RBRACE, std::string(1, m_contents[m_index - 1]));
		case '"': return Token(TokenType::TOKEN_STRING, collect_string());
		case '.': advance(); return Token(TokenType::TOKEN_PERIOD, std::string(1, m_contents[m_index - 1]));
		case '[': advance(); return Token(TokenType::TOKEN_LBRACKET, std::string(1, m_contents[m_index - 1]));
		case ']': advance(); return Token(TokenType::TOKEN_RBRACKET, std::string(1, m_contents[m_index - 1]));
		}

		advance();
		++m_nline;
	}

	return Token(TokenType::TOKEN_EOF, "");
}


void json::utils::Lexer::advance()
{
	if (++m_index < m_contents.size())
	{
		m_current_char = m_contents[m_index];
	}
}


std::string json::utils::Lexer::collect_string()
{
	std::string str;
	advance();

	while (m_current_char != '"' && m_index < m_contents.size() && m_current_char != '\n')
	{
		str += m_current_char;
		advance();
	}

	advance();
	return str;
}


std::string json::utils::Lexer::collect_int()
{
	std::string integer;

	while (isdigit(m_current_char) && m_index < m_contents.size() && m_current_char != '\n')
	{
		integer += m_current_char;
		advance();
	}

	return integer;
}