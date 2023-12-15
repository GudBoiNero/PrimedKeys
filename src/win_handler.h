#ifndef WIN_HANDLER
#define WIN_HANDLER

#ifndef WIN32 | WIN64
#include <Windows.h>
#endif

namespace handler {
	LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	HHOOK SetHook();
	void Unhook();
}

#endif 