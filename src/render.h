#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "emscripten/emscripten_mainloop_stub.h"
#endif

namespace render
{
	inline SDL_WindowFlags window_flags;
	inline SDL_Window* window;
	inline SDL_GLContext gl_context;

	// Determines when the window should exit
	inline bool done = false;

	inline char title[] = "PrimedKeys";

	inline ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	void Setup();
	void Cleanup();

	void BeginRender();
	void Render();
	void EndRender();
}