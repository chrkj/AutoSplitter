#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

enum Offsets
{
	STAR = 0xE01AB218,
	LEVEL = 0xE019DDFA
};

class GameProcess
{
public:
	GameProcess(const char* processName);
	void Update();
	
public:
	int Stars;
	int CurLevel;

private:
	short ReadMemory(unsigned int offset);
	void GetHandle();
	void GetProcessID();

private:
	DWORD m_ProcessId;
	BYTE* m_BaseAddress;
	HANDLE m_ProcessHandle;
	const char* m_ProcessName;
};

