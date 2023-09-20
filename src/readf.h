#ifndef READF_H
#define READF_H

#include <iostream>

//quick read file function for shader files
namespace readf
{
	std::string ReadFile(const std::string& filePath);
}
#endif // READF_H