#pragma once
#include <string>


namespace args
{
	namespace parse
	{
		inline bool active = false;
		inline std::string json_path;

		inline std::string selected_key;
	}

	void parse_args(int argc, char** argv);
	void help();

	void cmd_parse(int argc, char** argv);
	void help_parse();

	std::string argv_get(int argc, char** argv, int i);
}