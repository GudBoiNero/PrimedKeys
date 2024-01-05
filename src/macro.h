#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>
#include <texture.h>

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

	tex::Tex icon_tex;
	tex::Tex bg_tex;
	tex::Tex bg_hover_tex;
	tex::Tex bg_active_tex;
public:
	Macro(
		const std::string name,
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

	void LoadTextures()
	{
		tex::LoadTextureFromFile(icon_path().c_str(), &icon_tex);
		tex::LoadTextureFromFile(bg_path().c_str(), &bg_tex);
		tex::LoadTextureFromFile(bg_hover_path().c_str(), &bg_hover_tex);
		tex::LoadTextureFromFile(bg_active_path().c_str(), &bg_active_tex);
	}
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

JSONCONS_ALL_CTOR_GETTER_TRAITS(MacroFile, macros);
JSONCONS_N_CTOR_GETTER_TRAITS(Macro, 1, name, icon_path, bg_path, bg_hover_path, bg_active_path, is_inline, keys);
JSONCONS_ALL_CTOR_GETTER_TRAITS(MacroKey, key, action);

class MacroManager {
public:
	static MacroFile GetMacroFile() noexcept;
	// load macros from a JSON file
	static MacroFile LoadMacroFile(const std::string& file_path) noexcept;
	static void WriteMacroFile(const MacroFile& macroFile, const std::string& file_path = "macros.json") noexcept;
};

#endif // MACRO_H
