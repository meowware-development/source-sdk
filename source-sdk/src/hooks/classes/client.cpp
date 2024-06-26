#include "../hooks.hpp"

#include "../../utils/input/input.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"

void __fastcall src::hooks::Client::HudUpdate::HookFn(void* ecx, void* edx, bool active)
{
	static auto original = hook.GetOriginal<decltype(&HookFn)>();

	// Meant for any updating the cheat has to do every tick (eg. Input)
	utils::input::Update();

	return original(ecx, edx, active);
}
