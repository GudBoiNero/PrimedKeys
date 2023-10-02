#include "user_config.h"

std::string user_config::GetFolderPath()
{
#ifdef _WIN32 || _WIN64 // Windows

	{
		// https://stackoverflow.com/questions/11587426/get-current-username-in-c-on-windows

		char username[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserName(username, &username_len);

		return std::format("C:Users/{}/AppDataLocal/PrimedKeys", username);
	};
#elif __APPLE__ || __MACH__ // Mac OS
	{

	};
#elif __LINUX__ || __unix || __unix__ // Linux/Unix
	{
		return "/etc/pk"
	};
#endif

	return std::string();
}
