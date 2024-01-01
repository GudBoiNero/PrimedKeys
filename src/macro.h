#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class MacroKey {
	std::string key_;
	std::string action_;

public:
	MacroKey(const std::string key = "", const std::string action = "") : key_(key), action_(action)
	{
	}

	std::string key() const { return key_; }
	std::string action() const { return action_; }
};

class Macro {
	std::string name_;
	std::vector<MacroKey> keys_;

	std::string icon_path_;
	std::string bg_path_;
	std::string bg_hover_path_;
	std::string bg_active_path_;

	bool is_inline_;
public:
	Macro(
		const std::string name = "",
		const std::string icon_path = "",
		const std::string bg_path = "",
		const std::string bg_hover_path = "",
		const std::string bg_active_path = "",
		const bool is_inline = false,
		const std::vector<MacroKey> keys = {}
	) : name_(name), icon_path_(icon_path), bg_path_(bg_path), bg_hover_path_(bg_hover_path), bg_active_path_(bg_active_path), is_inline_(is_inline), keys_(keys)
	{
	}

	const std::string name() const { return name_; }
	const std::vector<MacroKey> keys() const { return keys_; }

	const std::string icon_path() const { return icon_path_; };
	const std::string bg_path() const { return icon_path_; }
	const std::string bg_hover_path() const { return bg_hover_path_; }
	const std::string bg_active_path() const { return bg_active_path_; }

	const bool is_inline() const { return is_inline_; }
};

class MacroFile
{
	std::vector<Macro> macros_;
public:
	MacroFile(const std::vector<Macro> macros = {}) : macros_(macros)
	{
	}

	const std::vector<Macro> macros() const { return macros_; }
};

class MacroManager {
public:
	static std::vector<Macro> GetMacros() noexcept;
	// load macros from a JSON file
	static std::vector<Macro> LoadMacros(const std::string& filePath) noexcept;
	static void WriteMacros(const std::vector<Macro>& macroList, const std::string& filePath = "macros.json") noexcept;
};

#endif // MACRO_H
