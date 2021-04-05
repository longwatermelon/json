#pragma once
#include <string>


namespace json::utils
{
	enum class TokenType
	{
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_STRING,
		TOKEN_INT,
		TOKEN_PERIOD,
		TOKEN_LBRACKET,
		TOKEN_RBRACKET,
		TOKEN_EOF
	};

	class Token
	{
	public:
		TokenType type{ TokenType::TOKEN_EOF };
		std::string value;

		Token() = default;

		Token(TokenType type, const std::string& value)
			: type(type), value(value)
		{}
	};
}