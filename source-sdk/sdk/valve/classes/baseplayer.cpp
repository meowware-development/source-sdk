#include "baseplayer.hpp"

#include "../../../utils/memory/memory.hpp"

#include "../datatypes/usercmd.hpp"

#include "../../interfaces/interfaces.hpp"

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
	if (IsAlive()) {
		Vector3* min, * max;
		if (GetFlags() & FL_DUCKING) {
			min = &sdk::interfaces::gameRules->GetViewVectors()->duckHullMin;
			max = &sdk::interfaces::gameRules->GetViewVectors()->duckHullMax;
		}
		else {
			min = &sdk::interfaces::gameRules->GetViewVectors()->hullMin;
			max = &sdk::interfaces::gameRules->GetViewVectors()->hullMax;
		}

		SetCollisionBounds(min, max);

		if (GetFlags() & FL_ONGROUND)
			*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xE34) = 0;

		if (GetSequence() == -1)
			SetSequence(0);

		StudioFrameAdvance();
	}

	static auto simulatePlayerSimulatedEntites = utils::memory::PatternScan(utils::memory::GetModule("client.dll"),
		"E8 ?? ?? ?? ?? 8B 06 8B CE 5E 5B").Relative<void(__thiscall*)(BasePlayer*)>();

	simulatePlayerSimulatedEntites(this);

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

void BasePlayer::SetCollisionBounds(Vector3* min, Vector3* max)
{
	static auto function = utils::memory::PatternScan(utils::memory::GetModule("client.dll"),
		"E8 ?? ?? ?? ?? 53 E8 ?? ?? ?? ?? 83 C4 ?? 5F 84 C0").Relative<void(__thiscall*)(uintptr_t, Vector3*, Vector3*)>();
	function(reinterpret_cast<uintptr_t>(this) + 0x19C, min, max);
}

int BasePlayer::GetSequence()
{
	return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x7C0);
}

void BasePlayer::SetSequence(int newSequence)
{
	utils::memory::CallVirtualFunction<void>(this, 185, newSequence);
}

void BasePlayer::StudioFrameAdvance()
{
	utils::memory::CallVirtualFunction<void>(this, 186);
}

int BasePlayer::GetSimulationTick()
{
	return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xCC);
}

void BasePlayer::SetSimulationTick(int newSimTick)
{
	*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xCC) = newSimTick;
}

CommandContext* BasePlayer::GetCommandContext()
{
	return nullptr;
}
