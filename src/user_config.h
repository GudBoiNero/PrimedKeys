#ifndef PK_USER_CONFIG_H
#define PK_USER_CONFIG_H

#include <format>

#ifdef _WIN32 || _WIN64 // Windows
#include <windows.h>
#include <Lmcons.h>
#elif __APPLE__ || __MACH__ // Mac OS

#elif __LINUX__ || __unix || __unix__ // Linux/Unix

#endif

#include <iostream>

namespace user_config
{
	std::string GetFolderPath();
}

#endif // PK_USER_CONFIG_H