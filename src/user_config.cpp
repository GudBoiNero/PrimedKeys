#include "user_config.h"

#include "macro.h"
#include <format>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <filesystem>

inline const std::vector<Macro> default_macros = {
	Macro {
		"undo",
		{
			MacroKey { "ctrl", "down" },
			MacroKey { "z",    "down" },
			MacroKey { "z",      "up" },
			MacroKey { "ctrl",   "up" }
		},
		"images\\buttons\\icon_undo.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"arrow_up",
		{
			MacroKey { "up", "down" },
			MacroKey { "up",   "up" }
		},
		"images\\buttons\\icon_arrow_up.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"redo",
		{
			MacroKey { "ctrl", "down" },
			MacroKey { "shift","down" },
			MacroKey { "z",    "down" },
			MacroKey { "z",      "up" },
			MacroKey { "shift",  "up" },
			MacroKey { "ctrl",   "up" }
		},
		"images\\buttons\\icon_redo.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		false,
	},
	Macro {
		"arrow_left",
		{
			MacroKey { "left", "down" },
			MacroKey { "left",   "up" }
		},
		"images\\buttons\\icon_arrow_left.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"pause",
		{
			MacroKey { "space", "down" },
			MacroKey { "space",   "up" }
		},
		"images\\buttons\\icon_pause.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"arrow_right",
		{
			MacroKey { "right", "down" },
			MacroKey { "right",   "up" }
		},
		"images\\buttons\\icon_arrow_right.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		false
	},Macro {
		"copy",
		{
			MacroKey { "ctrl", "down" },
			MacroKey { "c",    "down" },
			MacroKey { "c",      "up" },
			MacroKey { "ctrl",   "up" }
		},
		"images\\buttons\\icon_clipboard.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"arrow_down",
		{
			MacroKey { "down", "down" },
			MacroKey { "down",   "up" }
		},
		"images\\buttons\\icon_arrow_down.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		true
	},
	Macro {
		"pase",
		{
			MacroKey { "ctrl", "down" },
			MacroKey { "v",    "down" },
			MacroKey { "v",      "up" },
			MacroKey { "ctrl",   "up" }
		},
		"images\\buttons\\icon_paste.png",
		"images\\buttons\\button.png",
		"images\\buttons\\button_hover.png",
		"images\\buttons\\button_active.png",
		false,
	}
};

std::string user_config::GetConfigFolderPath()
{
	// Return environment variable path if it exists AND it is valid
	auto env_path = getenv("PK_CONFIG_PATH");
	if (env_path ? IsValidConfigFolderPath(env_path) : false)
		return env_path;

	std::string path;
#ifdef _WIN32 || _WIN64 // Windows
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);

	path = std::format("C:\\Users\\{}\\AppData\\Local\\PrimedKeys", username);
#elif __APPLE__ || __MACH__ // Mac OS
	path = std::format("\\Users\\{}\\Library\\Application Support\\PrimedKeys", getenv("USER"));
#elif __LINUX__ || __unix || __unix__ // Linux/Unix
	path = "/etc/pk";
#endif

	// If it's not a valid folder path, attempt to initialize one.
	if (!IsValidConfigFolderPath(path))
		InitConfigFolder(path);

	return path;
}

std::string user_config::GetMacroFilePath()
{
	return std::format("{}\\{}", GetConfigFolderPath(), default_macros_file_name);
}

bool user_config::IsValidConfigFolderPath(std::string folder_path)
{
	std::string macros_json_path = std::format("{}\\{}", folder_path, default_macros_file_name);

	bool has_directory = false;
	{
		// Does the directory exist?
		if (access(folder_path.c_str(), 0) == 0)
		{
			struct stat status;
			stat(folder_path.c_str(), &status);

			if (status.st_mode & S_IFDIR)
				has_directory = true; // Yea
		}
	}

	bool has_macros_json = false;
	bool macros_json_valid = false;
	{
		if (access(macros_json_path.c_str(), 0) == 0)
		{
			struct stat status;
			stat(macros_json_path.c_str(), &status);

			if (status.st_mode & S_IFDIR);
			else
			{
				has_macros_json = true;
				try {
					MacroManager::LoadMacros(macros_json_path);
					macros_json_valid = true;
				}
				catch (...) {}
			}
		}
	}

	return has_directory && macros_json_valid;
}

void user_config::InitConfigFolder(std::string path)
{
	try {
		std::filesystem::create_directories(path);

		std::string macro_file_path = std::format("{}\\{}", path, default_macros_file_name);
		
		MacroManager::WriteMacros(default_macros, macro_file_path);
	}
	catch (...) {}
};