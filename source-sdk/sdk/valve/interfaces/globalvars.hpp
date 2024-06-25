#pragma once

struct GlobalVars {
	float realTime;
	int frameCount;
	float absoluteFrametime;
	float absoluteFrameStartTime;
	float curTime;
	float frameTime;
	int maxClients;
	int tickCount;
	float intervalPerTick;
	float interpolation_amount;
	int simTicksThisFrame;
	int networkProtocol;
	void* pSaveData;
	bool isClient;
	bool isRemoteClient;
	int timestampNetworkingBase;
	int timestampRandomizeWindow;
};