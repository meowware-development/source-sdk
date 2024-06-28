#include "baseplayer.hpp"
#include "../../../utils/memory/memory.hpp"

bool BasePlayer::IsAlive()
{
	return (GetLifeState() == LIFE_ALIVE);
}

void BasePlayer::SetLocalViewangles(Vector3 newAngle)
{
	utils::memory::CallVirtualFunction<void>(this, 293, newAngle);
}
