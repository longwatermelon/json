#pragma once
#include "parser.h"
#include <variant>


namespace json
{
	class Json
	{
	public:
		Json(std::map<std::string, std::unique_ptr<utils::Node>>& pairs);

		Json() = default;

		template <typename T>
		T& get(const std::string& key)
		{
			if (pairs.count(key) == 0)
			{
				throw std::runtime_error(key + " is not an existing key\n");
			}

			if constexpr (std::is_same_v<T, int>)
				return pairs[key]->int_value;

			if constexpr (std::is_same_v<T, std::string>)
				return pairs[key]->string_value;
		}

		template <typename T>
		void set(const std::string& key, const T& value)
		{
			std::unique_ptr<utils::Node> val = std::make_unique<utils::Node>(utils::NodeType::NODE_NOOP);

			if constexpr (std::is_same_v<T, int>)
			{
				val->type = utils::NodeType::NODE_INT;
				val->int_value = value;
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				val->type = utils::NodeType::NODE_STRING;
				val->string_value = value;
			}
			else
			{
				return;
			}

			pairs[key] = std::move(val);
		}

	private:
		std::map<std::string, std::unique_ptr<utils::Node>> pairs;

		friend void dump(const std::string& fp, const Json& obj);
	};


	Json load_json_string(const std::string& json_string);
	Json load_from_path(const std::string& fp);
	void dump(const std::string& fp, const Json& obj);
}