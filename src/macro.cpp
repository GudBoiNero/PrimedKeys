#include "macro.h"
#include "user_config.h"

MacroFile MacroManager::GetMacroFile() noexcept
{
	MacroFile macro_file;
	try { macro_file = LoadMacroFile(user_config::GetMacroFilePath()); }
	catch (...) {}
	return macro_file;
};

// load macros from a JSON file
MacroFile MacroManager::LoadMacroFile(const std::string& file_path) noexcept 
{
	std::fstream f(file_path);
	std::stringstream iss;
	iss << f.rdbuf();
	std::string data = iss.str();

	MacroFile macro_file;
	
	try {
		macro_file = jsoncons::decode_json<MacroFile>(data);
	}
	catch(jsoncons::conv_error err) {}

	return macro_file;
}

void MacroManager::WriteMacroFile(const MacroFile& macro_file, const std::string& file_path) noexcept 
{
	std::string data;

	try {
		jsoncons::encode_json<MacroFile>(macro_file, data, jsoncons::indenting::indent);

		// Only write data if it's successfully encoded.
		std::ofstream out(file_path);
		out << data;
		out.close();
	}
	catch(jsoncons::conv_error) {}
}