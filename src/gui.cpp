#include "gui.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace gui
{
    void ShowMacroMenu(bool p_open) {
        ImGui::Begin("MacroMenu", &p_open, default_window_flags);
        ImGui::GetWindowViewport()->Flags = default_viewport_flags;

        {
            const char img_icon[] = "images/buttons/button.png";

			gui::TextureButton((ImGuiID)"_pktb1", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb2", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb3", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb4", img_icon, ImGuiButtonFlags_None); 

			gui::TextureButton((ImGuiID)"_pktb5", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb6", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb7", img_icon, ImGuiButtonFlags_None); ImGui::SameLine();
			gui::TextureButton((ImGuiID)"_pktb8", img_icon, ImGuiButtonFlags_None);
        }

		ImGui::End();
	}

    // https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users
    // Simple helper function to load an image into a OpenGL texture with common settings
    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
    {
        // Load from file
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);

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

	struct TextureButtonData
	{
		ImTextureID texture = 0;
		int width = 0;
		int height = 0;
	};
	inline const char btn_img_default[] = "images/buttons/button.png";
	inline const char btn_img_hover[] = "images/buttons/button_hover.png";
	inline const char btn_img_active[] = "images/buttons/button_active.png";
	TextureButtonData btn_default_data;
	TextureButtonData btn_hover_data;
	TextureButtonData btn_active_data;
	ImVec2 btn_size;
	ImVec2 btn_uv0 = ImVec2(0.0f, 0.0f);
	ImVec2 btn_uv1 = ImVec2(1.0f, 1.0f);
	ImVec4 btn_bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 btn_tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	void LoadNativeTextures()
	{
		bool ret = LoadTextureFromFile(btn_img_default, (GLuint*)(void*)&btn_default_data.texture, &btn_default_data.width, &btn_default_data.height);
		IM_ASSERT(ret);
		ret = LoadTextureFromFile(btn_img_hover, (GLuint*)(void*)&btn_hover_data.texture, &btn_hover_data.width, &btn_hover_data.height);
		IM_ASSERT(ret);
		ret = LoadTextureFromFile(btn_img_active, (GLuint*)(void*)&btn_active_data.texture, &btn_active_data.width, &btn_active_data.height);
		IM_ASSERT(ret);

		btn_size = ImVec2(btn_default_data.width, btn_default_data.height);
	}

	// Custom Textures
	bool TextureButton(ImGuiID id, const char img_icon[], ImTextureID texture_default_id, ImTextureID texture_hover_id, ImTextureID texture_active_id, ImGuiButtonFlags flags)
	{
		ImTextureID texture_id = texture_default_id;
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
		if (btn_bg_col.w > 0.0f)
			window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(btn_bg_col));
		window->DrawList->AddImage(texture_id, bb.Min + padding, bb.Max - padding, btn_uv0, btn_uv1, ImGui::GetColorU32(btn_tint_col));

		return pressed;
	}

	// Native textures
	bool TextureButton(ImGuiID id, const char img_icon[], ImGuiButtonFlags flags)
	{
		return TextureButton(id, img_icon, btn_default_data.texture, btn_hover_data.texture, btn_active_data.texture, flags);
	}
}