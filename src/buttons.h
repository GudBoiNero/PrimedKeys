#pragma once

#include "gui.h"

#include <iostream>
#include <imgui.h>
#include <imgui_internal.h>
#include <SDL_opengl.h>

namespace gui
{
	struct TextureButtonData
	{
		ImTextureID texture = 0;
		int width = 0;
		int height = 0;
	};
	
	/*bool PKImageButton(
		ImGuiID texture,
		TextureButtonData img_default_data,
		TextureButtonData img_hover_data,
		TextureButtonData img_active_data)
	{
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);
		ImVec2 uv1 = ImVec2(img_default_data.width / img_default_data.width, img_default_data.height / img_default_data.height);
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		const ImVec2 size = ImVec2(img_default_data.width, img_default_data.height);
		bool clicked = ImGui::ImageButtonEx(ImGuiID(1), (void*)(intptr_t)texture, size, uv0, uv1, bg_col, tint_col, ImGuiButtonFlags_None);

		texture = img_default_data.texture;
		if (clicked)
		{
			std::cout << "Pressed\n";
			texture = img_active_data.texture;
		}

		return clicked;
	}*/

	bool TextureButton(
		ImGuiID id,
		ImTextureID texture_id,
		ImTextureID texture_hover_id,
		ImTextureID texture_active_id,
		const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1,
		const ImVec4& bg_col, const ImVec4& tint_col,
		ImGuiButtonFlags flags)
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		const ImVec2 padding = g.Style.FramePadding;
		const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2.0f);
		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

		// Determine image
		if (hovered)
		{
			//std::cout << "Hovered!";
			texture_id = texture_hover_id;
		}
		if (pressed || held)
		{
			//std::cout << "Pressed!";
			texture_id = texture_active_id;
		}

		// Render
		//const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		const ImU32 col = ImGui::GetColorU32(ImGuiCol_Button);
		ImGui::RenderNavHighlight(bb, id);
		ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
		if (bg_col.w > 0.0f)
			window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bg_col));
		window->DrawList->AddImage(texture_id, bb.Min + padding, bb.Max - padding, uv0, uv1, ImGui::GetColorU32(tint_col));

		return pressed;
	}
}