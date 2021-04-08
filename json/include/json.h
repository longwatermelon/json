#pragma once
#include "parser.h"
#include "utils.h"
#include <any>


namespace json
{
	class Json
	{
	public:
		Json(std::map<std::string, std::unique_ptr<utils::Node>>& pairs);
		Json(std::vector<json_variant>& v);

		Json() = default;

		json_variant& operator[](const std::string& key);
		json_variant& operator[](int index);

		utils::Node& get_raw(const std::string& key);

	private:
		std::map<std::string, std::unique_ptr<utils::Node>> m_pairs;
		std::vector<json_variant> m_list;

		friend void dump(const std::string& fp, const Json& obj);
	};


	Json load_json_string(const std::string& json_string);
	Json load_from_path(const std::string& fp);
	void dump(const std::string& fp, const Json& obj);
}