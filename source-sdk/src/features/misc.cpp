#include "misc.hpp"

#include "../../globals.hpp"

void src::features::BunnyHop(UserCmd* cmd)
{
	if (!globals::localPlayer->IsAlive())
		return;

	int moveType = globals::localPlayer->GetMoveType();

	if (moveType & MOVETYPE_LADDER)
		return;

	if (!(globals::localPlayer->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}
