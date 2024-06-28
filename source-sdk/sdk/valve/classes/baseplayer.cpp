#include "baseplayer.hpp"
#include "../../../utils/memory/memory.hpp"

void BasePlayer::SetLocalViewangles(Vector3 newAngle)
{
	utils::memory::CallVirtualFunction<void>(this, 293, newAngle);
}

void BasePlayer::UpdateButtonStates(int buttonMask)
{
	static auto function = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "55 8B EC 8B 81 ?? ?? ?? ?? 8B D0").Cast<int(__thiscall*)(BasePlayer*, int)>();
	function(this, buttonMask);
}
