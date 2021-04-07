#pragma once
#include "utils.h"
#include <string>
#include <memory>
#include <variant>


namespace json::utils
{
	enum class NodeType
	{
		NODE_PAIR,
		NODE_LITERAL,
		NODE_NOOP
	};

	enum class LiteralType
	{
		INT,
		STRING,
		LIST
	};

	

	class Node
	{
	public:
		NodeType type{ NodeType::NODE_NOOP };

		Node(NodeType type)
			: type(type) {}

		// pair
		std::string pair_first;
		std::unique_ptr<Node> pair_second;

		// literal
		json_variant literal_value;
		LiteralType literal_type{ LiteralType::INT };

		void operator=(const json_variant& v)
		{
			literal_value = v;

			switch (v.index())
			{
			case 0: literal_type = LiteralType::STRING; break;
			case 1: literal_type = LiteralType::INT; break;
			case 2: literal_type = LiteralType::LIST; break;
			}
		}
	};
}