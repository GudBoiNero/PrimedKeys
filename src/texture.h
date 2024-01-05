#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <iostream>
#include <imgui.h>
#include <map>
#include <vector>

namespace tex
{

	struct Tex
	{
		ImTextureID id = (void*)-1;
		int width = 0;
		int height = 0;

		Tex() = default;
	};

	// https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
	// Simple helper function to load an image into a OpenGL texture with common settings
	bool LoadTextureFromFile(const char* filename, GLuint* out_id, int* out_width, int* out_height);
	bool LoadTextureFromFile(const char* filename, tex::Tex* out_texture);

	// Uses a hash of the file_path and all of the shader_paths. It's called `crap_hash` for a reason. 
	// It could really be done better. But it works for now.
	// It's used so we can determine the difference between `apple.png` and `apple.png` + `shader.glsl`
	static inline std::map<std::string, Tex> tex_cache = {};
	Tex GetTexture(const std::string file_path);
}

#endif // TEXTURE_H