#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <imgui.h>
#include <readf.h>
#include <map>

namespace tex
{
	inline std::string fragShaderString = ::ReadFile("src/frag.glsl");
	inline char* fragShaderSource = const_cast<char*>(fragShaderString.c_str());

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

#endif // TEXTURE_H