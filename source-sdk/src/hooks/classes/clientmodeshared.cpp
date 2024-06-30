#include "../hooks.hpp"

#include "../../../globals.hpp"

#include "../../features/features.hpp"
#include "../../helpers/helpers.hpp"

bool __fastcall src::hooks::ClientMode::CreateMove::HookFn(void* thisptr, void* edx, float time, UserCmd* cmd)
{
	static auto original = hook.GetOriginal<decltype(&HookFn)>();

	// SendPacket is used for desync / fakelag
	// Set to true if you want to choke packets
	uintptr_t _bp; __asm mov _bp, ebp;
	bool* sendPacket = (bool*)(***(uintptr_t***)_bp - 0x1);

	// Fetch local player
	globals::localPlayer = BaseEntity::GetLocalEntity()->As<BasePlayer>();

	// Return if localPlayer is nullptr (shouldn't really happen)
	if (!globals::localPlayer) [[unlikely]]
		return original(sdk::interfaces::clientMode, edx, time, cmd);

	int oldFlags = globals::localPlayer->GetFlags();

	globals::prePredPosition = globals::localPlayer->GetAbsOrigin();

	features::BunnyHop(cmd);

	helpers::StartPrediction(cmd);

	helpers::FinishPrediction();

	globals::postPredPosition = globals::localPlayer->GetAbsOrigin();

	features::EdgeJump(oldFlags, cmd);

	return original(sdk::interfaces::clientMode, edx, time, cmd);
}