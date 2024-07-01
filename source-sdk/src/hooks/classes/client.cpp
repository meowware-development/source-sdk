#include "../hooks.hpp"

#include "../../../utils/input/input.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"

// Meant for any updating the cheat has to do every frame (eg. Input)
void __fastcall src::hooks::Client::HudUpdate::HookFn(void* thisptr, void* edx, bool active)
{
	static auto original = hook.GetOriginal<decltype(&HookFn)>();

	utils::input::Update();

	return original(sdk::interfaces::client, edx, active);
}
