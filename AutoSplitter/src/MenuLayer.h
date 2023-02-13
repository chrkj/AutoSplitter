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
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
		ImGui::Begin("Main", 0, flags);

		if (ImGui::Button("Connect"))
		{
			m_NetworkSocket->TryConnect();
		}

		ImGui::End();
	}
private:
	NetworkSocket* m_NetworkSocket;
};