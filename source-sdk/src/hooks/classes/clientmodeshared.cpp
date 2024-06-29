#include "../hooks.hpp"

#include "../../../globals.hpp"

#include "../../features/features.hpp"
#include "../../helpers/helpers.hpp"

bool __stdcall src::hooks::ClientMode::CreateMove::HookFn(float time, void* usercmd)
{
	using CreateMoveOriginal = bool(__thiscall*)(void*, float, void*);
	static auto original = hook.GetOriginal<CreateMoveOriginal>();

	uintptr_t _bp; __asm mov _bp, ebp;
	bool* sendPacket = (bool*)(***(uintptr_t***)_bp - 0x1);

	UserCmd* userCmd = reinterpret_cast<UserCmd*>(usercmd);

	// Fetch local player
	globals::localPlayer = BaseEntity::GetLocalEntity()->As<BasePlayer>();

	// Return if localPlayer is nullptr (shouldn't really happen)
	if (!globals::localPlayer)
		return original(sdk::interfaces::clientMode, time, usercmd);

	int oldFlags = globals::localPlayer->GetFlags();

	features::BunnyHop(userCmd);

	helpers::StartPrediction(userCmd);

	helpers::FinishPrediction();

	features::EdgeJump(oldFlags, userCmd);

	return original(sdk::interfaces::clientMode, time, usercmd);
}