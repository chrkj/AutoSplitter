#pragma once
#include <thread>
#include <comdef.h>

#include "Walnut/Application.h"

#include "GameProcess.h"
#include "NetworkSocket.h"

class MenuLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override
	{
		m_NetworkSocket = new NetworkSocket("127.0.0.1", 16834);
		m_GameProcess = new GameProcess("Project64.exe");
		m_GameProcess->GetProcessID();
		m_GameProcess->GetBaseAddress();
		m_GameProcess->GetHandle();
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Main", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::Button(m_NetworkSocket->IsConnected() ? "Connected" : "Connect"))
		{
			m_NetworkSocket->Connect();
		}

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


		ImGui::End();
	}
private:
	GameProcess* m_GameProcess;
	NetworkSocket* m_NetworkSocket;
};