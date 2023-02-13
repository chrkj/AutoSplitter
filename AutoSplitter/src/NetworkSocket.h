#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

class NetworkSocket
{
public:
	NetworkSocket(const char* address, int port);
	void Connect();
	void Split();
	void Reset();
	void TryConnect();
	bool IsConnected();

private:
	int m_port;
	const char* m_address;
	SOCKET m_connection;
	bool m_isConnected;
};

