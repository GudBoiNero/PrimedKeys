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


	
	return macros;
}

void MacroManager::WriteMacros(const std::vector<Macro>& macros, const std::string& filePath) noexcept {
	
}