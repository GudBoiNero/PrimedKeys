#include "macro.h"
#include "user_config.h"

std::vector<Macro> MacroManager::GetMacros() noexcept
{
	std::vector<Macro> macros;
	try { macros = LoadMacros(user_config::GetMacroFilePath()); }
	catch (...) {}
	return macros;
};

// ISSUE: Need to fix the macro file if any properties are missing. https://github.com/GudBoiNero/PrimedKeys/issues/43
// load macros from a JSON file
std::vector<Macro> MacroManager::LoadMacros(const std::string& filePath) noexcept {
	std::vector<Macro> macros;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Could not open the file " << filePath << std::endl;
		return macros;
	}

	nlohmann::json j;
	file >> j;

	for (const auto& json_macro : j) {
		Macro macro;
		
		if (json_macro.contains("name"))
			macro.name = json_macro["name"].get<std::string>();
		if (json_macro.contains("is_inline"))
			macro.is_inline = json_macro["is_inline"].get<bool>();
		else 
			macro.is_inline = false;
		if (json_macro.contains("icon_path"))
			macro.icon_path = json_macro["icon_path"].get<std::string>();
		if (json_macro.contains("bg_path"))
			macro.bg_path = json_macro["bg_path"].get<std::string>();
		if (json_macro.contains("bg_hover_path"))
			macro.bg_hover_path = json_macro["bg_hover_path"].get<std::string>();
		if (json_macro.contains("bg_active_path"))
			macro.bg_active_path = json_macro["bg_active_path"].get<std::string>();

		for (const auto& input : json_macro["inputs"]) {
			MacroKey macro_key;
			if (input.contains("key"))
				macro_key.key = input["key"];
			if (input.contains("action"))
				macro_key.action = input["action"];
			macro.keys.push_back(macro_key);
		}

		macros.push_back(macro);
	}
	return macros;
}

void MacroManager::WriteMacros(const std::vector<Macro>& macros, const std::string& filePath) noexcept {
	nlohmann::json j;

	for (const auto& macro : macros) {
		nlohmann::json json_macro;
		json_macro["name"] = macro.name;
		json_macro["is_inline"] = macro.is_inline;
		json_macro["icon_path"] = macro.icon_path;
		json_macro["bg_path"] = macro.bg_path;
		json_macro["bg_hover_path"] = macro.bg_hover_path;
		json_macro["bg_active_path"] = macro.bg_active_path;

		nlohmann::json inputs = nlohmann::json::array();
		for (const auto& k : macro.keys) {
			nlohmann::json key;
			key["key"] = k.key;
			key["action"] = k.action;
			inputs.push_back(key);
		}

		json_macro["inputs"] = inputs;
		j.push_back(json_macro);
	}

	std::ofstream file(filePath);
	if (file.is_open()) {
		file << j.dump(4);
	}
	else {
		std::cerr << "Could not open the file for writing: " << filePath << std::endl;
	}
}