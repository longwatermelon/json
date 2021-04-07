#pragma once
#include <variant>
#include <string>
#include <vector>


namespace json
{
	class vector;
}

#define json_variant std::variant<std::string, int, json::vector>

namespace json
{
	class vector
	{
	public:
		vector() = default;

		vector(const std::vector<json_variant>& vec)
			: m_vector(vec) {}

		void append(const json_variant& v)
		{
			m_vector.emplace_back(v);
		}

		json_variant& operator[](int i)
		{
			return m_vector[i];
		}

		std::vector<json_variant> get() { return m_vector; }

	private:
		std::vector<json_variant> m_vector;
	};
}