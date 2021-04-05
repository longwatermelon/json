#include "json/include/json.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main()
{
	std::string path = "example.json";
	std::ifstream f(path);
	std::stringstream ss;
	std::string line;

	while (std::getline(f, line)) ss << line << "\n";

	f.close();

	json::Json dumped;
	dumped.set("key", 1);
	dumped.set("key 1", std::string("value")); // c style strings dont work, std::string() is required

	json::dump("example.json", dumped);

	json::Json loaded = json::load_from_path("example.json");

	std::cout << loaded.get<int>("key") << " " << loaded.get<std::string>("key 1") << "\n";

	return 0;
}