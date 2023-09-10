#pragma once

#include <imgui.h>

namespace gui
{
	// TODO: Allow for the macro menu to show up without the main window behind it.
	constexpr ImGuiWindowFlags default_window_flags = ImGuiWindowFlags_AlwaysAutoResize; 

	void ShowMacroMenu() {
		bool p_open = false;

		ImGui::Begin("Macro Menu", &p_open, default_window_flags);

		ImGui::Button("Undo", { 40, 20 });
		ImGui::Button("Redo", { 40, 20 });

		ImGui::End();
	}
}