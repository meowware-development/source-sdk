#include "baseplayer.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../structures/usercmd.hpp"

bool BasePlayer::IsAlive()
{
	return (GetLifeState() == LIFE_ALIVE);
}

void BasePlayer::SetLocalViewangles(Vector3 newAngle)
{
	utils::memory::CallVirtualFunction<void>(this, 293, newAngle);
}

void BasePlayer::PreThink()
{
	utils::memory::CallVirtualFunction<void>(this, 253);
}

void BasePlayer::Think()
{
	utils::memory::CallVirtualFunction<void>(this, 121);
}

void BasePlayer::PostThink()
{
	utils::memory::CallVirtualFunction<void>(this, 254);
}

int BasePlayer::GetNextThinkTick()
{
	static auto function = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "55 8B EC 8B 45 ?? 56 8B F1 85 C0 75").Cast<int(__thiscall*)(BasePlayer*, int)>();
	return function(this, 0);
}

void BasePlayer::SetNextThinkTick(float nextTick)
{
	static auto function = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "55 8B EC F3 0F 10 45 ?? 0F 2E 05 ?? ?? ?? ?? 53").Cast<
		char(__thiscall*)(BasePlayer*, float, int)>();
	function(this, nextTick, 0);
}

void BasePlayer::UpdateButtonStates(int buttonMask)
{
	static auto function = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "55 8B EC 8B 81 ?? ?? ?? ?? 8B D0").Cast<int(__thiscall*)(BasePlayer*, int)>();
	function(this, buttonMask);
}

void BasePlayer::SetCurrentCommand(UserCmd* command)
{
	// TODO: Sigscan for offset
	*reinterpret_cast<UserCmd**>(reinterpret_cast<uintptr_t>(this) + 0x101C) = command;
}

void BasePlayer::SelectItem(const char* name, int subType)
{
	utils::memory::CallVirtualFunction<void>(this, 263, name, subType);
}

void BasePlayer::SetImpulse(int impulse)
{
	// TODO: Sig for offset
	*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x10C4) = impulse;
}
