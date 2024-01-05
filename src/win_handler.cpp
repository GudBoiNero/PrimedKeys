#include "win_handler.h"
#include <iostream>

HHOOK hook{};
DWORD process_id, thread_id;
HWND* focused_window;

LRESULT CALLBACK handler::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		focused_window = (HWND*)wParam;

        char wnd_title[256];
        GetWindowText(*focused_window, wnd_title, sizeof(wnd_title));
        std::cout << wnd_title << std::endl;
	}

	return 0;
}

HHOOK handler::SetHook()
{
    HWND foreground_window = GetForegroundWindow();

    if (foreground_window != NULL) {
        // Get the process ID and thread ID of the foreground window
        thread_id = GetWindowThreadProcessId(foreground_window, &process_id);

        if (thread_id != 0 && process_id != 0) {
            if (process_id != GetCurrentProcessId()) // Prevent hooking our own application
            {
                hook = SetWindowsHookEx(WH_CBT, handler::CBTProc, 0, thread_id);
                std::cout << "Hooked Thread ID: " << thread_id << std::endl;
            }
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

void handler::Unhook()
{
	UnhookWindowsHookEx(hook);
}