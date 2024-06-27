#pragma once
#include "../../math/vector.hpp"
#include "../structures/movedata.hpp"

class BasePlayer;

class GameMovement
{
public:
	virtual			~GameMovement(void) {}

	// Process the current movement command
	virtual void	ProcessMovement(BasePlayer* pPlayer, MoveData* pMove) = 0;
	virtual void	StartTrackPredictionErrors(BasePlayer* pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(BasePlayer* pPlayer) = 0;
	virtual void	DiffPrint(char const* fmt, ...) = 0;

	// Allows other parts of the engine to find out the normal and ducked player bbox sizes
	virtual Vector3	GetPlayerMins(bool ducked) const = 0;
	virtual Vector3	GetPlayerMaxs(bool ducked) const = 0;
	virtual Vector3  GetPlayerViewOffset(bool ducked) const = 0;

};