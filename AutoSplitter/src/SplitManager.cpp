#include "SplitManager.h"

void SplitManager::Update(NetworkSocket* networkSocket, GameProcess* gameProcess)
{
	if (gameProcess->Stars == 30848 && RestartFlag)
	{
		ResetData();
		RestartFlag = false;
		networkSocket->Reset();
		networkSocket->Split();
	}
	else
	{
		RestartFlag = true;
	}

	if (gameProcess->Stars == 1 && gameProcess->CurLevel == Level::LOBBY && BOB_SPLIT) 
	{
		networkSocket->Split();
		BOB_SPLIT = false;
	}

	if (gameProcess->Stars == 6 && gameProcess->CurLevel == Level::LOBBY && WF_SPLIT)
	{
		networkSocket->Split();
		WF_SPLIT = false;
	}

	if (gameProcess->Stars == 8 && gameProcess->CurLevel == Level::LOBBY && CCM_SPLIT)
	{
		networkSocket->Split();
		CCM_SPLIT = false;
	}

	if (gameProcess->Stars == 9 && gameProcess->CurLevel == Level::LOBBY && BITDW_SPLIT)
	{
		networkSocket->Split();
		BITDW_SPLIT = false;
	}

	if (gameProcess->Stars == 11 && gameProcess->CurLevel == Level::LOBBY && SSL_SPLIT) 
	{
		networkSocket->Split();
		SSL_SPLIT = false;
	}

	if (gameProcess->Stars == 12 && gameProcess->CurLevel == Level::LOBBY && LLL_SPLIT) 
	{
		networkSocket->Split();
		LLL_SPLIT = false;
	}

	if (gameProcess->Stars == 15 && gameProcess->CurLevel == Level::LOBBY && HMC_SPLIT) 
	{
		networkSocket->Split();
		HMC_SPLIT = false;
	}

	if (gameProcess->Stars == 15 && gameProcess->CurLevel == Level::DDD && MIPS_SPLIT) 
	{
		networkSocket->Split();
		MIPS_SPLIT = false;
	}

	if (gameProcess->Stars == 16 && gameProcess->CurLevel == Level::LOBBY && DDD_SPLIT) 
	{
		networkSocket->Split();
		DDD_SPLIT = false;
	}

	if (gameProcess->Stars == 16 && gameProcess->CurLevel == Level::LOBBY && FS_SPLIT) 
	{
		// TODO: Fix split
		networkSocket->Split();
		FS_SPLIT = false;
	}

	if (gameProcess->Stars == 16 && gameProcess->CurLevel == Level::BITS && BLJ_SPLIT) 
	{
		networkSocket->Split();
		BLJ_SPLIT = false;
	}

	if (gameProcess->Stars == 16 && gameProcess->CurLevel == Level::BOWSER_3 && BITS_SPLIT) 
	{
		networkSocket->Split();
		BITS_SPLIT = false;
	}

}

void SplitManager::ResetData()
{
	BOB_SPLIT = true;
	WF_SPLIT = true;
	CCM_SPLIT = true;
	BITDW_SPLIT = true;
	SSL_SPLIT = true;
	LLL_SPLIT = true;
	HMC_SPLIT = true;
	MIPS_SPLIT = true;
	DDD_SPLIT = true;
	FS_SPLIT = true;
	BLJ_SPLIT = true;
	BITS_SPLIT = true;
}
