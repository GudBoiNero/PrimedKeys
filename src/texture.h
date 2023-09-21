#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <iostream>
#include <imgui.h>
#include <readf.h>
#include <map>
#include <vector>

namespace tex
{
	inline std::string fragShaderString = readf::ReadFile("src/frag.glsl");
	inline char* fragShaderSource = const_cast<char*>(fragShaderString.c_str());

	// https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
	// Simple helper function to load an image into a OpenGL texture with common settings
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height, const std::string* shaders[] = {});

	struct Tex
	{
		ImTextureID* id;
		int width;
		int height;

		Tex() = default;
	};

	struct TexCacheKey
	{

	};

	struct TexCache : std::map<TexCacheKey, Tex>
	{

	};

	static inline TexCache texture_cache = {};
	Tex GetTextureID(const std::string file_path, const std::string shader_paths[] = {});
}

#endif // TEXTURE_H