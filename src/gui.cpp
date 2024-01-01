#include "gui.h"
#include "user_config.h"

namespace gui
{
	//bool playing = false;
	void ShowMacroMenu(bool* p_open) {
		ImGui::Begin("MacroMenu", p_open, default_window_flags);
		ImGui::GetWindowViewport()->Flags = default_viewport_flags;

		MacroFile macro_file;
		macro_file = MacroManager::GetMacroFile();
		std::vector<Macro> macros = macro_file.macros();

		for (int i = 0; i < macros.size(); i++)
		{
			Macro macro = macros[i];
			gui::MacroButton((ImGuiID)"macro_button_" + (char)1 + i, macro);
			if (macro.is_inline()) ImGui::SameLine();
		}

		ImGui::End();
	}	

	inline const char path_btn_default[] = "images/buttons/button.png";
	inline const char path_btn_hover[] = "images/buttons/button_hover.png";
	inline const char path_btn_active[] = "images/buttons/button_active.png";
	tex::Tex tex_btn_default;
	tex::Tex tex_btn_hover;
	tex::Tex tex_btn_active;

	ImVec2 btn_size;
	ImVec2 btn_uv0 = ImVec2(0.0f, 0.0f);
	ImVec2 btn_uv1 = ImVec2(1.0f, 1.0f);
	ImVec4 btn_bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 btn_tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	void ReloadTextures()
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

	bool MacroButton(ImGuiID id, Macro macro)
	{
		bool val = TextureButton(id, tex::GetTextureID(macro.icon_path()).id, tex::GetTextureID(macro.bg_path()).id, tex::GetTextureID(macro.bg_hover_path()).id, tex::GetTextureID(macro.bg_active_path()).id, ImGuiButtonFlags_None);
		return val;
	}
}