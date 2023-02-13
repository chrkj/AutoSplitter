#pragma once
#include <Windows.h>
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

class NetworkSocket
{
public:
	NetworkSocket(const char* address, int port)
		: m_address(address), m_port(port) 
	{}

	bool TryConnect()
	{
		WSAData wsaData;
		WORD DllVersion = MAKEWORD(2, 1);
		if (WSAStartup(DllVersion, &wsaData) != 0)
		{
			std::cout << "Winsock Connection Failed!" << std::endl;
			return false;
		}
		IN_ADDR ipvalue;
		SOCKADDR_IN addr;
		int addrLen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(16834);
		addr.sin_family = AF_INET;

		m_connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(m_connection, (SOCKADDR*)&addr, addrLen) == 0)
		{
			std::cout << "Connected!" << std::endl;
			return true;
		}
		std::cout << "Error Connecting to Host" << std::endl;
		return false;
	}

private:
	int m_port;
	const char* m_address;
	SOCKET m_connection;
};

