#include "user_config.h"

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

bool user_config::IsValidConfigFolderPath(std::string path)
{
	// Does the directory exist?
	if (access(path.c_str(), 0) == 0)
	{
		struct stat status;
		stat(path.c_str(), &status);

		if (status.st_mode & S_IFDIR)
			return true; // Yea
	}

	return false; // Nope
}

void user_config::InitConfigFolder(std::string path)
{
	try {
		std::filesystem::create_directories(path);
	}
	catch (...) {}
};