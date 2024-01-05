#ifndef GUI_H
#define GUI_H

#include "texture.h"
#include "macro.h"
#include <imgui_internal.h>

namespace gui
{
	// TODO: Allow for the macro menu to show up without the main window behind it.
	constexpr ImGuiWindowFlags default_window_flags =
		ImGuiWindowFlags_AlwaysAutoResize;

	constexpr ImGuiViewportFlags default_viewport_flags =
		ImGuiViewportFlags_NoDecoration |
		ImGuiViewportFlags_TopMost |
		ImGuiViewportFlags_NoFocusOnClick |
		ImGuiViewportFlags_NoFocusOnAppearing |
		ImGuiViewportFlags_NoTaskBarIcon;

	void ShowMacroMenu(bool* p_open);
	void HandleMacroPress(Macro macro);

#pragma region TextureButton
	bool TextureButton(ImGuiID id, tex::Tex icon_tex, ImGuiButtonFlags flags);
	bool TextureButton(ImGuiID id, tex::Tex icon_tex, tex::Tex default_tex, tex::Tex hover_tex, tex::Tex active_tex, ImGuiButtonFlags flags);
	bool MacroButton(ImGuiID id, Macro macro);
#pragma endregion
}

#endif // GUI_H