#include "GameProcess.h"

GameProcess::GameProcess(const char* processName)
	: m_processName(processName)
{}

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
				std::string processName(m_processName);
				std::wstring wProcessName(processName.begin(), processName.end());
				std::wstring wCurrentProcess(pe.szExeFile);
				if (wProcessName.compare(wCurrentProcess) == 0)
				{
					m_processId = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe));
		}
	}
}

void GameProcess::GetBaseAddress()
{
	MODULEENTRY32 mod_entry = { 0 };
	void* snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_processId);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 current = { 0 };
		current.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(snapshot, &current))
		{
			do
			{
				std::string processName(m_processName);
				std::wstring wProcessName(processName.begin(), processName.end());
				std::wstring wCurrentProcess(current.szModule);
				if (wProcessName.compare(wCurrentProcess) == 0)
				{
					mod_entry = current;
					break;
				}
			} while (Module32Next(snapshot, &current));
		}
	}
	m_baseAddress = mod_entry.modBaseAddr;
}

void GameProcess::GetHandle()
{
	m_processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_processId);
	if (m_processHandle == NULL)
		printf("Can't open process with id: %u\n", m_processId);
}

short GameProcess::ReadMemory(unsigned int offset)
{
	BYTE* address = m_baseAddress;
	address += offset;
	address -= 0x400000;

	short dataBuffer;
	BOOL success = ReadProcessMemory(m_processHandle, (LPCVOID)address, &dataBuffer, sizeof(DWORD), nullptr);
	if (!success)
	{
		printf("Can't read memory from address 0x%x\n", address);
		return EXIT_FAILURE;
	}
	return dataBuffer;
}
