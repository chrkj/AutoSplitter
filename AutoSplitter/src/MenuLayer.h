#pragma once
#include <thread>
#include <comdef.h>

#include "Walnut/Application.h"

#include "GUI.h"
#include "GameProcess.h"
#include "NetworkSocket.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if (wParam == WM_KEYDOWN) 
	{
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (kbdStruct->vkCode == VK_F1)
			printf("Reset pressed (%d)\n", kbdStruct->vkCode);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

class MenuLayer : public Walnut::Layer
{
public:

	~MenuLayer()
	{
		UnhookWindowsHookEx(hook);
	}

	virtual void OnAttach() override
	{
		m_GameProcess = std::make_shared<GameProcess>("Project64.exe");
		m_NetworkSocket = std::make_shared<NetworkSocket>("127.0.0.1", 16834);
		GUI::SetStyle();
		hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	}

	virtual void OnUIRender() override
	{
		ImGui::ShowDemoWindow();
		ImGui::Begin("Main", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::Button("Connect"))
		{
			m_NetworkSocket->Connect();
		}

		ImGui::SameLine(150);
		if (m_NetworkSocket->IsConnected())
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Connected");
		else
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Connected");

		if (ImGui::Button("Split"))
		{
			m_NetworkSocket->Split();
		}

		if (ImGui::Button("Reset"))
		{
			m_NetworkSocket->Reset();
		}

		if (ImGui::Button("Level"))
		{
			std::cout << m_GameProcess->ReadMemory(Offsets::LEVEL) << std::endl;
		}

		if (ImGui::Button("Star"))
		{
			std::cout << m_GameProcess->ReadMemory(Offsets::STAR) << std::endl;
		}

		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);


		ImGui::End();
	}

	

private:
	std::shared_ptr<GameProcess> m_GameProcess;
	std::shared_ptr<NetworkSocket> m_NetworkSocket; 
	HHOOK hook;
};