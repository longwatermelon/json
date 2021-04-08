#include "../include/json.h"
#include <iostream>
#include <fstream>


json::Json::Json(std::map<std::string, std::unique_ptr<utils::Node>>& pairs)
	: m_pairs(std::move(pairs)) {}


json::Json::Json(std::vector<json_variant>& v)
	: m_list(v) {}


json_variant& json::Json::operator[](const std::string& key)
{
	if (m_pairs.count(key) == 0)
	{
		using namespace json::utils;
		std::unique_ptr<Node> node = std::make_unique<Node>(NodeType::NODE_LITERAL);
		m_pairs[key] = std::move(node);
	}
	
	return m_pairs[key]->literal_value;
}


json_variant& json::Json::operator[](int index)
{
	return m_list[index];
}


json::utils::Node& json::Json::get_raw(const std::string& key)
{
	if (m_pairs.count(key) == 0)
	{
		using namespace json::utils;
		std::unique_ptr<Node> node = std::make_unique<Node>(NodeType::NODE_LITERAL);
		m_pairs[key] = std::move(node);
	}

	return *(m_pairs[key].get());
}


json::Json json::load_json_string(const std::string& json_string)
{
	utils::Parser parser(json_string);
	parser.parse();

	if (parser.m_map.size() > 0)
		return Json(parser.m_map);
	else
		return Json(parser.m_list);
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

		if (pair.second->literal_type == utils::LiteralType::STRING)
			val << '"' << std::get<std::string>(pair.second->literal_value) << '"';

		else if (pair.second->literal_type == utils::LiteralType::INT)
			val << std::get<int>(pair.second->literal_value);

		else if (pair.second->literal_type == utils::LiteralType::LIST)
		{
			// ADD DUMPING HERE LATER
		}

		std::stringstream ss;
		ss << key << ": " << val.str() << ",\n\t";

		output += ss.str();
	}

	output.replace(output.end() - 3, output.end(), "\n");
	output += "}";

	f << output;
	f.close();
}