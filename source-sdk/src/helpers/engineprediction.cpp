#include "engineprediction.hpp"
#include "../../sdk/sdk.hpp"
#include "../../globals.hpp"

void src::helpers::StartPrediction(UserCmd* cmd)
{
	if (!globals::localPlayer || !globals::localPlayer->IsAlive() || !globals::moveHelper)
		return;

	static auto physicsRunThink = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "E8 ?? ?? ?? ?? 84 C0 74 0A 8B 07 8B CF FF 90 ?? ?? ?? ?? 6A").Relative<bool(__thiscall*)(BasePlayer*, int)>();
	static auto resetInstanceCounter = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "68 ?? ?? ?? ?? 6A ?? 68 ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4").Cast<void(__stdcall*)()>();
	resetInstanceCounter();

	sdk::interfaces::prediction->m_bInPrediction = true;

	if (!predictionRandomSeed || !predictedPlayer) {
		predictionRandomSeed = *reinterpret_cast<int**>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "A3 ?? ?? ?? ?? 5D C3 55 8B EC 8B 45 08").GetValue() + 1);
		predictedPlayer = *reinterpret_cast<int**>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "89 3D ?? ?? ?? ?? F3 0F 2A 87").GetValue() + 2);
	}

	static GlobalVars* globals = sdk::interfaces::playerInfoManager->GetGlobalVars();

	oldCurTime = globals->curtime;
	oldFrameTime = globals->frametime;

	globals::localPlayer->SetCurrentCommand(cmd);

	globals->curtime = globals::localPlayer->GetTickBase() * globals->intervalPerTick;
	globals->frametime = sdk::interfaces::prediction->m_bEnginePaused ? 0.f : globals->intervalPerTick;

	*predictionRandomSeed = cmd->randomSeed;
	*predictedPlayer = *reinterpret_cast<int*>(globals::localPlayer);

	sdk::interfaces::movement->StartTrackPredictionErrors(globals::localPlayer);

	if (cmd->weaponSelect) {
		BaseWeaapon* weapon = sdk::interfaces::entityList->GetClientEntityFromHandle(globals::localPlayer->GetActiveWeapon())->As<BaseWeaapon>();

		if (weapon) 
			globals::localPlayer->SelectItem(weapon->GetName(), cmd->weaponSubtype);
	}

	if (cmd->impulse)
		globals::localPlayer->SetImpulse(cmd->impulse);

	globals::localPlayer->UpdateButtonStates(cmd->buttons);

	globals::localPlayer->SetLocalViewangles(cmd->viewAngles);

	if (physicsRunThink(globals::localPlayer, 0)) {
		globals::localPlayer->PreThink();
		LOG(DebugLevel::NONE, "Called BasePlayer->PreThink()!");
	}

	int nextThink = globals::localPlayer->GetNextThinkTick();
	if (nextThink > 0 && nextThink <= globals::localPlayer->GetTickBase()) {
		globals::localPlayer->SetNextThinkTick();
		globals::localPlayer->Think();
	}

	sdk::interfaces::prediction->SetupMove(globals::localPlayer, cmd, globals::moveHelper, globals::moveData);

	sdk::interfaces::movement->ProcessMovement(globals::localPlayer, globals::moveData);

	sdk::interfaces::prediction->FinishMove(globals::localPlayer, cmd, globals::moveData);

	globals::localPlayer->PostThink();
}

void src::helpers::FinishPrediction()
{
	if (!globals::localPlayer || !globals::localPlayer->IsAlive() || !globals::moveHelper)
		return;

	static GlobalVars* globals = sdk::interfaces::playerInfoManager->GetGlobalVars();

	sdk::interfaces::movement->FinishTrackPredictionErrors(globals::localPlayer);

	globals::localPlayer->SetCurrentCommand(0);

	*predictionRandomSeed = -1;
	*predictedPlayer = 0;

	if (globals->frametime > 0)
		globals::localPlayer->GetTickBase()++;

	if (oldFrameTime != 0) {
		globals->frametime = oldFrameTime;
		globals->curtime = oldCurTime;
	}

	sdk::interfaces::prediction->m_bInPrediction = false;
}
