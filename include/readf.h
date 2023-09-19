#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

//quick read file function for shader files
namespace ReadFile {
	std::string ReadFile(const std::string& filePath) {
		std::ifstream file(filePath);
		if (!file.is_open()) {
			// if file cant be opened
			std::cout << "file couldnt be opened!";
			return "";
		}

		std::string line;
		std::string content;

		// loop through the lines of the file and add to content
		while (std::getline(file, line)) {
			content += line + "\n";
		}

		// close the file after the loop and return the contents of the file
		file.close();
		return content;
	}
}