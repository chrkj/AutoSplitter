#pragma once
#include <stdio.h>
#include <Windows.h>
#include "NetworkSocket.h"

class SplitManager
{
public:
	SplitManager();
	~SplitManager();
	void Update();

private:
	HHOOK m_Hook;
};

