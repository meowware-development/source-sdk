#include "engineprediction.hpp"
#include "../../sdk/sdk.hpp"
#include "../../globals.hpp"

void src::helpers::StartPrediction(UserCmd* cmd)
{
	if (!globals::localPlayer || !globals::localPlayer->IsAlive() || !globals::moveHelper)
		return;

	/*static auto resetInstanceCounter = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "E8 ?? ?? ?? ?? 8B 7D ?? 8B 5D ?? 53").Relative<void(__stdcall*)()>();
	resetInstanceCounter();*/

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

	globals::localPlayer->PreThink();

	int nextThink = globals::localPlayer->GetNextThinkTick();
	if (nextThink > 0 && nextThink <= globals::localPlayer->GetTickBase()) {
		globals::localPlayer->SetNextThinkTick();
		globals::localPlayer->Think();
	}

	static MoveData* moveData = **utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "FF 35 ?? ?? ?? ?? 8B 4D ?? FF 75").Cast<MoveData***>(2);

	sdk::interfaces::prediction->SetupMove(globals::localPlayer, cmd, globals::moveHelper, moveData);

	sdk::interfaces::movement->ProcessMovement(globals::localPlayer, moveData);

	sdk::interfaces::prediction->FinishMove(globals::localPlayer, cmd, moveData);

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
}
