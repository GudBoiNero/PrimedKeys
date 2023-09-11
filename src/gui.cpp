#include <imgui.h>
#include <SDL_opengl.h>
#include "gui.h"
#include "buttons.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gui
{
    void ShowMacroMenu(bool p_open) {
        ImGui::Begin("MacroMenu", &p_open, default_window_flags);
        ImGui::GetWindowViewport()->Flags = default_viewport_flags;

        /*{
            TextureButtonData img_default_data;
            TextureButtonData img_hover_data;
            TextureButtonData img_active_data;

            const char img_icon[] = "images/buttons/button.png";
            const char img_default[] = "images/buttons/button.png";
            const char img_hover[] = "images/buttons/button.png";
            const char img_active[] = "images/buttons/button.png";

            bool ret = LoadTextureFromFile(img_default, &img_default_data.texture, &img_default_data.width, &img_default_data.height);
            IM_ASSERT(ret);
            ret = LoadTextureFromFile(img_hover, &img_hover_data.texture, &img_hover_data.width, &img_hover_data.height);
            IM_ASSERT(ret);
            ret = LoadTextureFromFile(img_active, &img_active_data.texture, &img_active_data.width, &img_active_data.height);
            IM_ASSERT(ret);

            ImGuiID texture;

            gui::PKImageButton(texture, img_default_data, img_hover_data, img_active_data);
        }*/

        {
            TextureButtonData default_data;
            TextureButtonData hover_data;
            TextureButtonData active_data;

            const char img_icon[] = "images/buttons/button.png";
            const char img_default[] = "images/buttons/button.png";
            const char img_hover[] = "images/buttons/button_hover.png";
            const char img_active[] = "images/buttons/button_active.png";

            bool ret = LoadTextureFromFile(img_default, (GLuint*)(void*)&default_data.texture, &default_data.width, &default_data.height);
            IM_ASSERT(ret);
            ret = LoadTextureFromFile(img_hover, (GLuint*)(void*)&hover_data.texture, &hover_data.width, &hover_data.height);
            IM_ASSERT(ret);
            ret = LoadTextureFromFile(img_active, (GLuint*)(void*)&active_data.texture, &active_data.width, &active_data.height);
            IM_ASSERT(ret);

            ImVec2 size = ImVec2(default_data.width, default_data.height);
            ImVec2 uv0 = ImVec2(0.0f, 0.0f);
            ImVec2 uv1 = ImVec2(size / size);
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

            gui::TextureButton((ImGuiID)"Hello", default_data.texture, hover_data.texture, active_data.texture, size, uv0, uv1, bg_col, tint_col, ImGuiButtonFlags_None);
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
}