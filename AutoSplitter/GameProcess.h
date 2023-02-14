#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

enum Offsets
{
	STAR = 0xE01AB218,
	LEVEL = 0xE019DDFA
};

class GameProcess
{
public:
	GameProcess(const char* processName);
	void GetProcessID();
	void GetBaseAddress();
	void GetHandle();
	short ReadMemory(unsigned int offset);

private:
	const char* m_processName;
	DWORD m_processId;
	BYTE* m_baseAddress;
	HANDLE m_processHandle;
};

