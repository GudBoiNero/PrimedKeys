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
    HHOOK hook;
    HWND foregroundWindow = GetForegroundWindow();

    if (foregroundWindow != NULL) {
        // Get the process ID and thread ID of the foreground window
        DWORD process_id, thread_id;
        thread_id = GetWindowThreadProcessId(foregroundWindow, &process_id);

        if (thread_id != 0 && process_id != 0) {
            std::cout << "Foreground Window Process ID: " << process_id << std::endl;
            std::cout << "Foreground Window Thread ID: " << thread_id << std::endl;

            hook = SetWindowsHookEx(WH_CBT, handler::CBTProc, 0, thread_id);
        }
        else {
            std::cerr << "Error getting thread/process ID" << std::endl;
        }
    }
    else {
        std::cerr << "Error getting foreground window" << std::endl;
    }

	return hook;
}

void handler::Unhook(HHOOK hookHandle)
{
	UnhookWindowsHookEx(hookHandle);
}