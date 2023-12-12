#include "win_handler.h"
#include <iostream>

HWND* focusedWindow;

LRESULT CALLBACK handler::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		focusedWindow = (HWND*)wParam;

		std::cout << focusedWindow;
	}

	return 0;
}

HHOOK handler::SetHook()
{
	return SetWindowsHookEx(WH_CBT, handler::CBTProc, 0, GetCurrentThreadId());
}

void handler::Unhook(HHOOK hookHandle)
{
	UnhookWindowsHookEx(hookHandle);
}