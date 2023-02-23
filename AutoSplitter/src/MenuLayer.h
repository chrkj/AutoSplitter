#pragma once
#include <format>
#include <thread>
#include <comdef.h>

#include "Walnut/Application.h"

#include "GUI.h"
#include "GameProcess.h"
#include "SplitManager.h"
#include "NetworkSocket.h"

class MenuLayer : public Walnut::Layer
{
public:

	virtual void OnAttach() override
	{
		GUI::SetStyle();
		m_SplitManager = std::make_shared<SplitManager>();
		m_GameProcess = std::make_shared<GameProcess>("Project64.exe");
		m_NetworkSocket = std::make_shared<NetworkSocket>("127.0.0.1", 16834);
	}

	virtual void OnUIRender() override
	{
		m_GameProcess->Update();
		m_SplitManager->Update();

		ImGui::Begin("Main", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::Button("Connect"))
			m_NetworkSocket->Connect();

		ImGui::SameLine(150);
		if (m_NetworkSocket->IsConnected())
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Connected");
		else
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Connected");

		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), std::format("Stars: {}", m_GameProcess->Stars).c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), std::format("Current level: {}", m_GameProcess->CurLevel).c_str());

		ImGui::End();
	}

private:
	HHOOK m_Hook;
	std::shared_ptr<GameProcess> m_GameProcess;
	std::shared_ptr<SplitManager> m_SplitManager;
	std::shared_ptr<NetworkSocket> m_NetworkSocket; 
};