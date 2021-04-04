#include "include/json.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main()
{
	std::string path = "example.json";
	std::ifstream f(path);
	std::stringstream ss;
	std::string line;

	while (std::getline(f, line)) ss << line << "\n";

	f.close();

	/*json::utils::Lexer lexer(ss.str());

	json::utils::Token t(json::utils::TokenType::TOKEN_INT, "");

	while ((t = lexer.next_token()).type != json::utils::TokenType::TOKEN_EOF)
	{
		std::cout << t.value << "\n";
	}*/

	json::utils::Parser parser(ss.str());
	parser.parse();

	return 0;
}