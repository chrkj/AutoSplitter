#include "GameProcess.h"

GameProcess::GameProcess(const char* processName)
	: m_ProcessName(processName)
{
	GetProcessID();
	GetHandle();
}

void GameProcess::GetProcessID()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe))
		{
			do
			{
				std::string processName(m_ProcessName);
				std::wstring wProcessName(processName.begin(), processName.end());
				std::wstring wCurrentProcess(pe.szExeFile);
				if (wProcessName.compare(wCurrentProcess) == 0)
				{
					m_ProcessId = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe));
		}
	}
}

void GameProcess::GetHandle()
{
	m_ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_ProcessId);
	if (m_ProcessHandle == NULL)
		printf("Can't open process with id: %u\n", m_ProcessId);
}

void GameProcess::Update()
{
	Stars = ReadMemory(Offsets::STAR);
	CurLevel = ReadMemory(Offsets::LEVEL);
}

short GameProcess::ReadMemory(unsigned int offset)
{
	BYTE* address = (BYTE*)offset;
	short dataBuffer;
	BOOL success = ReadProcessMemory(m_ProcessHandle, (LPCVOID)address, &dataBuffer, sizeof(DWORD), nullptr);
	if (!success)
	{
		printf("Can't read memory from address 0x%x\n", address);
		return EXIT_FAILURE;
	}
	return dataBuffer;
}
