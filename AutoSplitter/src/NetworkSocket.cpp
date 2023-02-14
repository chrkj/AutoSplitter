#include "NetworkSocket.h"

NetworkSocket::NetworkSocket(const char* address, int port)
	: m_address(address), m_port(port), m_connection(0), m_isConnected(false)
{}

void NetworkSocket::Connect()
{
	std::thread t(&NetworkSocket::TryConnect, this);
	t.detach();	
}

void NetworkSocket::Split()
{
	const char* message = "startorsplit\r\n";
	if (send(m_connection, message, strlen(message), 0) == -1)
	{
		m_isConnected = false;
		std::cout << "Failed to send data to socket." << std::endl;
	}
}

void NetworkSocket::Reset()
{
	const char* message = "reset\r\n";
	if (send(m_connection, message, strlen(message), 0) == -1) 
	{
		m_isConnected = false;
		std::cout << "Failed to send data to socket." << std::endl;
	}
}

void NetworkSocket::TryConnect()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		m_isConnected = false;
		std::cout << "Winsock Connection Failed!" << std::endl;
	}

	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(16834);
	addr.sin_family = AF_INET;

	m_connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(m_connection, (SOCKADDR*)&addr, addrLen) == 0) 
	{
		m_isConnected = true;
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Error Connecting to Host." << std::endl;
	}
}

bool NetworkSocket::IsConnected()
{
	return m_isConnected;
}
