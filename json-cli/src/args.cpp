#include "../include/args.h"
#include "json/include/json.h"
#include <iostream>
#include <fstream>
#include <variant>


void args::parse_args(int argc, char** argv)
{
	if (argc == 1) help();
	if (strcmp(argv[1], "--help") == 0) help();

	else if (strcmp(argv[1], "parse") == 0)
	{
		parse::active = true;
		cmd_parse(argc, argv);

		json::Json loaded = json::load_from_path(parse::json_path);

		if (parse::selected_key.size() > 0)
		{
			json::utils::Node& value = loaded.get_raw(parse::selected_key);

			switch (value.literal_type)
			{
			case json::utils::LiteralType::INT: std::cout << std::get<int>(value.literal_value) << "\n"; break;
			case json::utils::LiteralType::STRING: std::cout << std::get<std::string>(value.literal_value) << "\n"; break;
			case json::utils::LiteralType::LIST:
			{
				for (auto& elem : std::get<json::vector>(value.literal_value).get())
				{
					switch (elem.index())
					{
					case 0: std::cout << std::get<std::string>(elem) << " "; break;
					case 1: std::cout << std::get<int>(elem) << " "; break;
					}
				}
			} break;
			}
		}
		else
		{
			switch (loaded[parse::selected_index].index())
			{
			case 1: std::cout << std::get<int>(loaded[parse::selected_index]) << "\n"; break;
			case 0: std::cout << std::get<std::string>(loaded[parse::selected_index]) << "\n"; break;
			default: std::cout << "unsupported data type\n"; break;
			}
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
		if (strcmp(argv[i], "-s") == 0)
		{
			++i;
			parse::selected_key = argv_get(argc, argv, i++);

			if (parse::selected_key[0] == '"')
			{
				parse::selected_key.erase(parse::selected_key.begin());
				parse::selected_key.erase(parse::selected_key.size() - 1, parse::selected_key.size());
			}
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			++i;
			parse::selected_index = std::stoi(argv_get(argc, argv, i++));
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