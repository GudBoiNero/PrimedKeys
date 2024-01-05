#include "gui.h"
#include "user_config.h"

#include "win_handler.h"

namespace gui
{
	//bool playing = false;
	void ShowMacroMenu(bool* p_open) {
		handler::SetHook();
		ImGui::Begin("MacroMenu", p_open, default_window_flags);
		ImGui::GetWindowViewport()->Flags = default_viewport_flags;

		MacroFile macro_file;
		macro_file = MacroManager::GetMacroFile();
		std::vector<Macro> macros = macro_file.macros();

		for (int i = 0; i < macros.size(); i++)
		{
			Macro macro = macros[i];
			macro.LoadTextures();
			bool pressed = gui::MacroButton((ImGuiID)"macro_button_" + (char)1 + i, macro);
			if (macro.is_inline()) ImGui::SameLine();

			if (pressed)
				HandleMacroPress(macro);
		}

		ImGui::End();
	}

	void HandleMacroPress(Macro macro) 
	{
#ifdef WIN32 | WIN64
#endif
	}

	inline const char btn_default_path[] = "images/buttons/button.png";
	inline const char btn_hover_path[] = "images/buttons/button_hover.png";
	inline const char btn_active_path[] = "images/buttons/button_active.png";
	
	ImVec2 btn_uv0 = ImVec2(0.0f, 0.0f);
	ImVec2 btn_uv1 = ImVec2(1.0f, 1.0f);
	ImVec4 btn_bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 btn_tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Custom Textures
	bool TextureButton(ImGuiID id, tex::Tex icon_tex, tex::Tex default_tex, tex::Tex hover_tex, tex::Tex active_tex, ImGuiButtonFlags flags)
	{
		ImVec2 btn_size = { (float)default_tex.width, (float)default_tex.height };
		ImTextureID tex_id = default_tex.id;
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
			tex_id = hover_tex.id;
			btn_size = { (float)hover_tex.width, (float)hover_tex.height };
			icon_offset = ImVec2(0, 1);
		}
		if (pressed || held)
		{
			//std::cout << "Pressed!";
			tex_id = active_tex.id;
			btn_size = { (float)active_tex.width, (float)active_tex.height };
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
		if (icon_tex.id)
			window->DrawList->AddImage(icon_tex.id, bb.Min + padding + icon_offset, bb.Max - padding + icon_offset, btn_uv0, btn_uv1, ImGui::GetColorU32(btn_tint_col));

		return pressed;
	}

	// Native textures
	bool TextureButton(ImGuiID id, tex::Tex icon_tex, ImGuiButtonFlags flags)
	{
		return TextureButton(id, icon_tex, tex::GetTexture(btn_default_path), tex::GetTexture(btn_hover_path), tex::GetTexture(btn_active_path), flags);
	}

	bool MacroButton(ImGuiID id, Macro macro)
	{
		bool val = TextureButton(id, tex::GetTexture(macro.icon_path()), tex::GetTexture(macro.bg_path()), tex::GetTexture(macro.bg_hover_path()), tex::GetTexture(macro.bg_active_path()), ImGuiButtonFlags_None);
		return val;
	}
}