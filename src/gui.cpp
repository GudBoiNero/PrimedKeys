#include "gui.h"
#include "readf.h"
#include <iostream>
#include <stdio.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif 

namespace gui
{
	bool playing = false;
	void ShowMacroMenu(bool p_open) {
		ImGui::Begin("MacroMenu", &p_open, default_window_flags);
		ImGui::GetWindowViewport()->Flags = default_viewport_flags;

		{
			gui::TextureButton((ImGuiID)"_pktb1",
				tex::GetTextureID("images\\buttons\\icon_arrow_left.png").id,
				ImGuiButtonFlags_None); ImGui::SameLine();

			bool play = gui::TextureButton((ImGuiID)"_pktb2",
				tex::GetTextureID(playing ? "images\\buttons\\icon_pause.png" : "images\\buttons\\icon_play.png").id,
				ImGuiButtonFlags_None); ImGui::SameLine();

			gui::TextureButton((ImGuiID)"_pktb3",
				tex::GetTextureID("images\\buttons\\icon_arrow_right.png").id,
				ImGuiButtonFlags_None);

			if (play) {
				playing = !playing;
			}
		}

		ImGui::End();
	}
	

	std::string fragShaderString = ReadFile::ReadFile("src/frag.glsl");

	const char* fragShaderSource = const_cast<char*>(fragShaderString.c_str());

    // https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
    // Simple helper function to load an image into a OpenGL texture with common settings
    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
    {
	GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragShaderSource, NULL);
	glCompileShader(FragShader);

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, FragShader);
	glLinkProgram(ShaderProgram);

        // Load from file
        int image_width = 0;
        int image_height = 0;
		
        unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;


	inline const char path_btn_default[] = "images/buttons/button.png";
	inline const char path_btn_hover[] = "images/buttons/button_hover.png";
	inline const char path_btn_active[] = "images/buttons/button_active.png";
	tex::Tex tex_btn_default;
	tex::Tex tex_btn_hover;
	tex::Tex tex_btn_active;

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);
		glUseProgram(ShaderProgram);
		glUniform1i(glGetUniformLocation(ShaderProgram, "textureSampler"), 1);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
        
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		*out_texture = image_texture;
		*out_width = image_width;
		*out_height = image_height;

		return true;
	}
  
	ImVec2 btn_size;
	ImVec2 btn_uv0 = ImVec2(0.0f, 0.0f);
	ImVec2 btn_uv1 = ImVec2(1.0f, 1.0f);
	ImVec4 btn_bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 btn_tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	void LoadNativeTextures()
	{
		bool ret = tex::LoadTextureFromFile(path_btn_default, (GLuint*)(void*)&tex_btn_default.id, &tex_btn_default.width, &tex_btn_default.height);
		IM_ASSERT(ret);
		ret = tex::LoadTextureFromFile(path_btn_hover, (GLuint*)(void*)&tex_btn_hover.id, &tex_btn_hover.width, &tex_btn_hover.height);
		IM_ASSERT(ret);
		ret = tex::LoadTextureFromFile(path_btn_active, (GLuint*)(void*)&tex_btn_active.id, &tex_btn_active.width, &tex_btn_active.height);
		IM_ASSERT(ret);

		btn_size = ImVec2(tex_btn_default.width, tex_btn_default.height);
	}

	// Custom Textures
	bool TextureButton(ImGuiID id, ImTextureID tex_icon_id, ImTextureID tex_default_id, ImTextureID tex_hover_id, ImTextureID tex_active_id, ImGuiButtonFlags flags)
	{
		ImTextureID tex_id = tex_default_id;
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		const ImVec2 padding = g.Style.FramePadding;
		const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + btn_size + padding * 2.0f);
		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
		ImVec2 icon_offset;

		// Determine image
		if (hovered)
		{
			//std::cout << "Hovered!";
			tex_id = tex_hover_id;
			icon_offset = ImVec2(0, 1);
		}
		if (pressed || held)
		{
			//std::cout << "Pressed!";
			tex_id = tex_active_id;
			icon_offset = ImVec2(0, 2);
		}

		// Render
		//const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		const ImU32 col = ImGui::GetColorU32(ImGuiCol_Button);
		ImGui::RenderNavHighlight(bb, id);
		ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
		if (btn_bg_col.w > 0.0f)
			window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(btn_bg_col));
		window->DrawList->AddImage(tex_id, bb.Min + padding, bb.Max - padding, btn_uv0, btn_uv1, ImGui::GetColorU32(btn_tint_col));
		if (tex_icon_id)
			window->DrawList->AddImage(tex_icon_id, bb.Min + padding + icon_offset, bb.Max - padding + icon_offset, btn_uv0, btn_uv1, ImGui::GetColorU32(btn_tint_col));

		return pressed;
	}

	// Native textures
	bool TextureButton(ImGuiID id, ImTextureID tex_icon_id, ImGuiButtonFlags flags)
	{
		return TextureButton(id, tex_icon_id, tex_btn_default.id, tex_btn_hover.id, tex_btn_active.id, flags);
	}
}