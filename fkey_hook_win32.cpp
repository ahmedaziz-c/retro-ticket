#include "fkey_hook.hpp"
#include <windows.h>

static HHOOK g_hook = nullptr;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM w, LPARAM l)
{
    if (nCode == HC_ACTION && w == WM_KEYDOWN) {
        auto* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(l);
        if (kb->vkCode >= VK_F1 && kb->vkCode <= VK_F12)
            return 1; // eaten
    }
    return CallNextHookEx(g_hook, nCode, w, l);
}

void fkey_hook::install()
{
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
}

void fkey_hook::uninstall()
{
    UnhookWindowsHookEx(g_hook);
}