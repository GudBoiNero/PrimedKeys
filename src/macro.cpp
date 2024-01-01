#include "macro.h"
#include "user_config.h"

MacroFile MacroManager::GetMacroFile() noexcept
{
	MacroFile macro_file;
	try { macro_file = LoadMacroFile(user_config::GetMacroFilePath()); }
	catch (...) {}
	return macro_file;
};

// ISSUE: Need to fix the macro file if any properties are missing. https://github.com/GudBoiNero/PrimedKeys/issues/43
// load macros from a JSON file
MacroFile MacroManager::LoadMacroFile(const std::string& file_path) noexcept {
	MacroFile macro_file;


	
	return macro_file;
}

void MacroManager::WriteMacroFile(const MacroFile& macro_file, const std::string& file_path) noexcept {
	
}