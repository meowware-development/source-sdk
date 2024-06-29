#pragma once

struct UserCmd;

namespace src::helpers {
	void StartPrediction(UserCmd* cmd);
	void FinishPrediction();

	inline int* predictedPlayer = nullptr;
	inline int* predictionRandomSeed = nullptr;

	inline float oldCurTime = 0.f;
	inline float oldFrameTime = 0.f;
}