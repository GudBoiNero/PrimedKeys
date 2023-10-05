#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <json.hpp>
#include <tuple>

struct MacroKey {
	std::string key = "";
	std::string action = "";
};

struct Macro {
	std::string name = "";
	std::vector<MacroKey> keys = {};
	std::string icon_path = "";
	std::string bg_path = "";
	std::string bg_hover_path = "";
	std::string bg_active_path = "";
};

using json = nlohmann::json;
class MacroManager {
public:
	static std::vector<Macro> GetMacros() noexcept;
	// load macros from a JSON file
	static std::vector<Macro> LoadMacros(const std::string& filePath = "path") noexcept;
	static void WriteMacros(const std::vector<Macro>& macroList, const std::string& filePath = "output.json") noexcept;
};

#endif // MACRO_H
