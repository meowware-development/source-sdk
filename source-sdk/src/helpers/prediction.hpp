#pragma once

struct UserCmd;
class BasePlayer;

namespace src::helpers {
	void StartPrediction(UserCmd* cmd);
	void RunPrediction(UserCmd* cmd);
	void FinishPrediction();
}