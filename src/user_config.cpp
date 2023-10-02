#include "user_config.h"

std::string user_config::GetFolderPath()
{
	// Return environment variable path if it exists AND it is valid
	auto env_path = getenv("PK_CONFIG_PATH");
	if (env_path)
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
	return path;
}
