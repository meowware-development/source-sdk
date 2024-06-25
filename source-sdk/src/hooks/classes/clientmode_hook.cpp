#include "../hooks.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../utils/debug/debug.hpp"

bool __stdcall src::hooks::ClientMode::CreateMove::HookFn(float time, void* usercmd)
{
	using CreateMoveOriginal = bool(__thiscall*)(void*, float, void*);
	static auto original = hook.GetOriginal<CreateMoveOriginal>();

	return original(sdk::interfaces::clientMode, time, usercmd);
}