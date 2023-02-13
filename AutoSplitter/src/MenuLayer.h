#pragma once
#include <thread>

#include "Walnut/Application.h"
#include "NetworkSocket.h"

class MenuLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override
	{
		m_NetworkSocket = new NetworkSocket("127.0.0.1", 16834);
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

		ImGui::End();
	}
private:
	NetworkSocket* m_NetworkSocket;
};