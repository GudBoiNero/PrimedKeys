#pragma once

#include <glad.h>
#include <iostream>
#include <map>
#include <imgui.h>
#include <imgui_internal.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace tex {

	// https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
	// Simple helper function to load an image into a OpenGL texture with common settings
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

	struct Tex
	{
		ImTextureID* id = 0;
		int width = 0;
		int height = 0;
	};

	static inline std::map<std::string, Tex> texture_cache = {};
	Tex GetTextureID(std::string file_path);
}
