#pragma once
#include <string>
#include <memory>


namespace json::utils
{
	enum class NodeType
	{
		NODE_PAIR,
		NODE_STRING,
		NODE_INT,
		NODE_NOOP
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

		// string
		std::string string_value;

		// int
		int int_value{ 0 };
	};
}