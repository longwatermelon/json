#include "../include/json.h"
#include <iostream>
#include <fstream>


json::Json::Json(std::map<std::string, std::unique_ptr<utils::Node>>& pairs)
	: m_pairs(std::move(pairs)) {}


std::unique_ptr<json::utils::Node>& json::Json::get_raw(const std::string& key)
{
	return m_pairs[key];
}


json::Json json::load_json_string(const std::string& json_string)
{
	utils::Parser parser(json_string);
	parser.parse();

	return Json(parser.m_map);
}


json::Json json::load_from_path(const std::string& fp)
{
	std::ifstream f(fp);
	std::stringstream ss;
	std::string line;

	while (std::getline(f, line)) ss << line << "\n";

	f.close();

	return load_json_string(ss.str());
}


void json::dump(const std::string& fp, const Json& obj)
{
	std::ofstream f(fp, std::ofstream::out | std::ofstream::trunc);
	std::string output = "{\n\t";

	for (const auto& pair : obj.m_pairs)
	{
		std::string key = '"' + pair.first + '"';

		std::stringstream val;

		if (pair.second->type == utils::NodeType::NODE_STRING)
			val << '"' << pair.second->string_value << '"';

		else if (pair.second->type == utils::NodeType::NODE_INT)
			val << pair.second->int_value;

		std::stringstream ss;
		ss << key << ": " << val.str() << ",\n\t";

		output += ss.str();
	}

	output.replace(output.end() - 3, output.end(), "\n");
	output += "}";

	f << output;
	f.close();
}