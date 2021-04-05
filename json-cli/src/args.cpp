#include "../include/args.h"
#include "json/include/json.h"
#include <iostream>
#include <fstream>


void args::parse_args(int argc, char** argv)
{
	if (argc == 1) help();
	if (strcmp(argv[1], "--help") == 0) help();

	else if (strcmp(argv[1], "parse") == 0)
	{
		parse::active = true;
		cmd_parse(argc, argv);

		json::Json loaded = json::load_from_path(parse::json_path);

		if (parse::selected_key.empty())
		{
			std::cout << "no key selected\n";
			return;
		}

		std::unique_ptr<json::utils::Node>& value = loaded.get_raw(parse::selected_key);

		switch (value->type)
		{
		case json::utils::NodeType::NODE_INT: std::cout << value->int_value << "\n"; break;
		case json::utils::NodeType::NODE_STRING: std::cout << value->string_value << "\n"; break;
		}
	}
}


void args::help()
{
	std::cout << "parse <file path> <args>: parse a json file\n";
	exit(0);
}


void args::cmd_parse(int argc, char** argv)
{
	if (argc >= 3)
		parse::json_path = argv_get(argc, argv, 2);
	else
		help_parse();

	if (parse::json_path == "--help") help_parse();

	{
		std::ifstream temp(parse::json_path);

		if (!temp)
		{
			std::cout << "invalid file path\n";
			exit(1);
		}
	}

	int i = 3;
	while (i < argc)
	{
		if (strcmp(argv[i++], "-s") == 0)
		{
			parse::selected_key = argv_get(argc, argv, i++);

			if (parse::selected_key[0] == '"')
			{
				parse::selected_key.erase(parse::selected_key.begin());
				parse::selected_key.erase(parse::selected_key.size() - 1, parse::selected_key.size());
			}
		}
		else
		{
			std::cout << "unrecognized flag " << argv[i] << "\n";
			exit(1);
		}
	}
}


void args::help_parse()
{
	std::cout << "-s <selected key>: prints out json value at the specified key\n";
	exit(0);
}


std::string args::argv_get(int argc, char** argv, int i)
{
	if (i >= argc)
	{
		return "";
	}
	else
	{
		return argv[i];
	}
}