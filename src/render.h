#ifndef RENDER_H
#define RENDER_H

#include "gui.h"
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>

#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "emscripten/emscripten_mainloop_stub.h"
#endif

namespace render
{
	//void(&PlatformHandleFocus)();
	//void(&PlatformHandleMacros)();

	inline SDL_Window* window;
	inline SDL_GLContext gl_context;
	inline ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	inline SDL_WindowFlags window_flags = (SDL_WindowFlags)(
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_ALLOW_HIGHDPI |
		SDL_WINDOW_SKIP_TASKBAR |
		SDL_WINDOW_HIDDEN |
		SDL_WINDOW_ALWAYS_ON_TOP);

	inline ImGuiConfigFlags config_flags =
		ImGuiConfigFlags_NavEnableKeyboard |
		ImGuiConfigFlags_NavEnableGamepad |
		ImGuiConfigFlags_DockingEnable |
		ImGuiConfigFlags_ViewportsEnable;

	inline bool done = false;
	inline char title[] = "PrimedKeys";

	inline bool show_macro_menu = true;

	void Render();
	void BeginRender();
	void EndRender();

	void Setup();
	void Cleanup();

	//void PlatformHandleFocus();
	//void PlatformHandleMacros();
}
#endif // RENDER_H