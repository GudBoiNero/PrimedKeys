#ifndef MACRO_H
#define MACRO_H

#include "user_config.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <json.hpp>

struct MacroData {
	std::string key = "";
	std::string action = "";
};

struct MacroObject {
	std::string name = "";
	std::vector<MacroData> keys = {};
};

using json = nlohmann::json;
class Macro {
public:
	static std::vector<MacroObject> GetMacros() {
		return LoadMacros(std::format("{}\\{}", user_config::GetConfigFolderPath(), "macros.json"));
	}
	// load macros from a JSON file
	static std::vector<MacroObject> LoadMacros(const std::string& filePath = "path") {
		std::vector<MacroObject> macroList;
		std::ifstream file(filePath);
		if (!file.is_open()) {
			std::cerr << "Could not open the file " << filePath << std::endl;
			return macroList;
		}

		nlohmann::json j;
		file >> j;

		for (const auto& macro : j) {
			MacroObject m;
			m.name = macro["name"].get<std::string>();
			for (const auto& input : macro["inputs"]) {
				MacroData k;
				k.key = input["key"];
				k.action = input["action"];
				m.keys.push_back(k);
			}
			macroList.push_back(m);
		}
		return macroList;
	}

	static void WriteMacros(const std::vector<MacroObject>& macroList, const std::string& filePath = "output.json") {
		nlohmann::json j;

		for (const auto& m : macroList) {
			nlohmann::json macro;
			macro["name"] = m.name;

			nlohmann::json inputs = nlohmann::json::array();
			for (const auto& k : m.keys) {
				nlohmann::json key;
				key["key"] = k.key;
				key["action"] = k.action;
				inputs.push_back(key);
			}

			macro["inputs"] = inputs;
			j.push_back(macro);
		}

		std::ofstream file(filePath);
		if (file.is_open()) {
			file << j.dump(4);
		}
		else {
			std::cerr << "Could not open the file for writing: " << filePath << std::endl;
		}
	}
};

#endif // MACRO_H
