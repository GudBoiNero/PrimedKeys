#pragma once

#include <imgui.h>

namespace gui
{
	// TODO: Allow for the macro menu to show up without the main window behind it.
	constexpr ImGuiWindowFlags default_window_flags = ImGuiWindowFlags_AlwaysAutoResize;
	constexpr ImGuiViewportFlags default_viewport_flags =
		ImGuiViewportFlags_NoDecoration |
		ImGuiViewportFlags_TopMost |
		ImGuiViewportFlags_NoTaskBarIcon;

	void ShowMacroMenu(bool p_open) {
		ImGui::Begin("MacroMenu", &p_open, default_window_flags);
		ImGui::GetWindowViewport()->Flags = default_viewport_flags;

		ImGui::Button("Undo", { 40, 20 });
		ImGui::Button("Redo", { 40, 20 });

		ImGui::End();
	}
}