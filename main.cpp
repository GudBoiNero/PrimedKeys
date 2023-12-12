// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include "render.h"
#include "user_config.h"
#include <thread>

// Main code
int main(int, char**)
{
	std::string config_folder_path = user_config::GetConfigFolderPath();
	if (!user_config::IsValidConfigFolderPath(config_folder_path))
		user_config::InitConfigFolder(config_folder_path);

	render::Setup();

#ifdef __EMSCRIPTEN__
	// For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
	// You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
	io.IniFilename = nullptr;
	EMSCRIPTEN_MAINLOOP_BEGIN
#else
	while (!render::done)
#endif
	{
		render::BeginRender();
		render::Render();
		render::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
#ifdef __EMSCRIPTEN__
	EMSCRIPTEN_MAINLOOP_END;
#endif
	render::Cleanup();

	return 0;
}
