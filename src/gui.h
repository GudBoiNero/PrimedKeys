#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <SDL_opengl.h>

namespace gui
{
	// TODO: Allow for the macro menu to show up without the main window behind it.
	constexpr ImGuiWindowFlags default_window_flags = 
		ImGuiWindowFlags_None;

	constexpr ImGuiViewportFlags default_viewport_flags =
		ImGuiViewportFlags_NoDecoration |
		ImGuiViewportFlags_TopMost |
		ImGuiViewportFlags_NoTaskBarIcon;

	void ShowMacroMenu(bool p_open);
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

#pragma region TextureButton
	void LoadTextureButtons();
	bool TextureButton(ImGuiID id, const char img_icon[], ImGuiButtonFlags flags);
#pragma endregion
}