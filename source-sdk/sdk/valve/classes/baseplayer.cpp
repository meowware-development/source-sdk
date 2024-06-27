#include "baseplayer.hpp"
#include "../../../utils/memory/memory.hpp"

void BasePlayer::SetLocalViewangles(Vector3 newAngle)
{
	utils::memory::CallVirtualFunction<void>(this, 293, newAngle);
}
