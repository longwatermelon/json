#include "json/include/json.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main()
{
	json::Json j = json::load_from_path("example.json");

	std::cout << std::get<std::string>(j["key 1"]) << "\n";
	std::string foo = std::get<std::string>(j["key 1"]);

	std::cout << std::get<int>(j["key"]) << "\n";
	int bar = std::get<int>(j["key"]);

	j.get_raw("UwU") = std::string("Your Mother");

	json::dump("example.json", j);

	return 0;
}
