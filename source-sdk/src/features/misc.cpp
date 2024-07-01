#include "misc.hpp"

#include "../../globals.hpp"

void src::features::BunnyHop(UserCmd* cmd)
{
	if (!globals::localPlayer->IsAlive())
		return;

	int moveType = globals::localPlayer->GetMoveType();

	if (moveType & MOVETYPE_LADDER || moveType & MOVETYPE_NOCLIP)
		return;

	if (!(globals::localPlayer->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}

void src::features::EdgeJump(int oldFlags, UserCmd* cmd)
{
	if (!globals::localPlayer->IsAlive())
		return;

	int moveType = globals::localPlayer->GetMoveType();

	if (moveType & MOVETYPE_LADDER || moveType & MOVETYPE_NOCLIP)
		return;

	// We are on the ground current tick, but we predicted that we will not be next tick
	if (oldFlags & FL_ONGROUND && !(globals::localPlayer->GetFlags() & FL_ONGROUND))
		cmd->buttons |= IN_JUMP;
}