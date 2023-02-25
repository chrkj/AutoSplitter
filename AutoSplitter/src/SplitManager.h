#pragma once
#include <stdio.h>
#include <Windows.h>
#include "NetworkSocket.h"

enum Level
{
	CASTLE = 1,
	ATHLETIC = 2,
	DONJON = 3,
	BBH = 4,
	CCM = 5,
	LOBBY = 6,
	HMC = 7,
	SSL = 8,
	BOB = 9,
	SL = 10,
	WDW = 11,
	JRB = 12,
	THI = 13,
	TTC = 14,
	RR = 15,
	CASTLE_FRONT = 16,
	BITDW = 17,
	VC = 18,
	BITFS = 19,
	SA = 20,
	BITS = 21,
	LLL = 22,
	DDD = 23,
	WF = 24,
	ENDING_IMAGE = 25,
	CASTLE_COURTYARD = 26,
	PSS = 27,
	COTMC = 28,
	TOTWC = 29,
	BOWSER_1 = 30,
	WING_MARIO = 31,
	YL = 32,
	BOWSER_2 = 33,
	BOWSER_3 = 34,
	DUMMY = 35,
	TTM = 36,
	IWTEST = 37,
	SAND = 38
};

class SplitManager
{
public:
	void Update(NetworkSocket* networkSocket, GameProcess* gameProcess);

private:
	void ResetData();

private:
	HHOOK m_Hook;
	bool RestartFlag;

	bool BOB_SPLIT = true;
	bool WF_SPLIT = true;
	bool CCM_SPLIT = true;
	bool BITDW_SPLIT = true;
	bool SSL_SPLIT = true;
	bool LLL_SPLIT = true;
	bool HMC_SPLIT = true;
	bool MIPS_SPLIT = true;
	bool DDD_SPLIT = true;
	bool FS_SPLIT = true;
	bool BLJ_SPLIT = true;
	bool BITS_SPLIT = true;

};