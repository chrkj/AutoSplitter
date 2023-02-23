#include "SplitManager.h"
#include "NetworkSocket.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (kbdStruct->vkCode == VK_F1)
		{
			printf("Reset pressed (%d)\n", kbdStruct->vkCode);
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

SplitManager::SplitManager()
	: m_Hook(SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0))
{
}

SplitManager::~SplitManager()
{
	UnhookWindowsHookEx(m_Hook);
}

void SplitManager::Update()
{
}
