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
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height, std::vector<std::string> shaders = {});

	struct Tex
	{
		ImTextureID* id;
		int width;
		int height;

		Tex() = default;
	};

	// Uses a hash of the file_path and all of the shader_paths. It's called `crap_hash` for a reason. 
	// It could really be done better. But it works for now.
	// It's used so we can determine the difference between `apple.png` and `apple.png` + `shader.glsl`
	static inline std::map<std::string, Tex> tex_cache = {};
	Tex GetTextureID(const std::string file_path, std::vector<std::string> shader_paths = {});
}

#endif // TEXTURE_H