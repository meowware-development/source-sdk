#include "../hooks.hpp"

#include "../../../globals.hpp"

#include "../../features/features.hpp"

bool __stdcall src::hooks::ClientMode::CreateMove::HookFn(float time, void* usercmd)
{
	using CreateMoveOriginal = bool(__thiscall*)(void*, float, void*);
	static auto original = hook.GetOriginal<CreateMoveOriginal>();

	uintptr_t _bp; __asm mov _bp, ebp;
	bool* sendPacket = (bool*)(***(uintptr_t***)_bp - 0x1);

	UserCmd* userCmd = reinterpret_cast<UserCmd*>(usercmd);

	globals::localPlayer = BaseEntity::GetLocalEntity()->As<BasePlayer>();

	if (!globals::localPlayer)
		return original(sdk::interfaces::clientMode, time, usercmd);

	features::BunnyHop(userCmd);

	sdk::interfaces::movement->StartTrackPredictionErrors(globals::localPlayer);

	sdk::interfaces::movement->FinishTrackPredictionErrors(globals::localPlayer);

	return original(sdk::interfaces::clientMode, time, usercmd);
}