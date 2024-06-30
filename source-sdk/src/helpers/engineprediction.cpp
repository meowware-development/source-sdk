#include "engineprediction.hpp"
#include "../../sdk/sdk.hpp"
#include "../../globals.hpp"

void src::helpers::StartPrediction(UserCmd* cmd)
{
	if (!globals::localPlayer->IsAlive())
		return;

	if (!predictionRandomSeed || !predictedPlayer) {
		predictionRandomSeed = *reinterpret_cast<int**>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "A3 ?? ?? ?? ?? 5D C3 55 8B EC 8B 45 08").GetValue(1));
		predictedPlayer = *reinterpret_cast<int**>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "89 3D ?? ?? ?? ?? F3 0F 2A 87").GetValue(2));
	}

	int simulationTick = globals::localPlayer->GetSimulationTick();
	if (simulationTick == sdk::interfaces::globalVars->tickcount)
		return;

	globals::localPlayer->SetSimulationTick(sdk::interfaces::globalVars->tickcount);

	if (!globals::localPlayer->GetGroundEntity()) 
		globals::localPlayer->GetFlags() &= ~FL_ONGROUND;
	
	if (globals::localPlayer->GetFlags() & FL_FROZEN) {
		cmd->forwardMove = 0;
		cmd->sideMove = 0;
		cmd->upMove = 0;
		cmd->buttons = 0;
		cmd->impulse = 0;
	}

	static auto physicsRunThink = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "E8 ?? ?? ?? ?? 84 C0 74 0A 8B 07 8B CF FF 90 ?? ?? ?? ?? 6A").Relative<bool(__thiscall*)(BasePlayer*, int)>();
	static auto resetInstanceCounter = utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "68 ?? ?? ?? ?? 6A ?? 68 ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4").Cast<void(__stdcall*)()>();
	resetInstanceCounter();
	
	oldCurTime = sdk::interfaces::globalVars->curtime;
	oldFrameTime = sdk::interfaces::globalVars->frametime;

	globals::localPlayer->SetCurrentCommand(cmd);

	sdk::interfaces::globalVars->curtime = globals::localPlayer->GetTickBase() * sdk::interfaces::globalVars->intervalPerTick;
	sdk::interfaces::globalVars->frametime = sdk::interfaces::prediction->m_bEnginePaused ? 0.f : sdk::interfaces::globalVars->intervalPerTick;

	*predictionRandomSeed = cmd->randomSeed;
	*predictedPlayer = *reinterpret_cast<int*>(globals::localPlayer);

	sdk::interfaces::movement->StartTrackPredictionErrors(globals::localPlayer);

	if (cmd->weaponSelect) {
		BaseWeapon* weapon = sdk::interfaces::entityList->GetClientEntityFromHandle(globals::localPlayer->GetActiveWeapon())->As<BaseWeapon>();

		if (weapon)
			globals::localPlayer->SelectItem(weapon->GetName(), cmd->weaponSubtype);
	}

	if (cmd->impulse)
		globals::localPlayer->SetImpulse(cmd->impulse);

	globals::localPlayer->UpdateButtonStates(cmd->buttons);

	globals::localPlayer->SetLocalViewangles(cmd->viewAngles);

	if (physicsRunThink(globals::localPlayer, 0))
		globals::localPlayer->PreThink();

	int nextThink = globals::localPlayer->GetNextThinkTick();
	if (nextThink > 0 && nextThink <= globals::localPlayer->GetTickBase()) {
		globals::localPlayer->SetNextThinkTick();
		globals::localPlayer->Think();
	}

	static MoveHelper* moveHelper = **reinterpret_cast<MoveHelper***>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "8B 15 ?? ?? ?? ?? 8B 41 08 8B").GetValue(2));
	
	MoveData moveData{};

	// No need to pass in moveHelper; its only used for veichle related shit
	sdk::interfaces::prediction->SetupMove(globals::localPlayer, cmd, moveHelper, &moveData);

	sdk::interfaces::movement->ProcessMovement(globals::localPlayer, &moveData);

	sdk::interfaces::prediction->FinishMove(globals::localPlayer, cmd, &moveData);

	globals::localPlayer->PostThink();
}

void src::helpers::FinishPrediction()
{
	if (!globals::localPlayer->IsAlive())
		return;

	sdk::interfaces::movement->FinishTrackPredictionErrors(globals::localPlayer);

	globals::localPlayer->SetCurrentCommand(nullptr);

	*predictionRandomSeed = -1;
	*predictedPlayer = 0;

	if (oldFrameTime != 0) {
		sdk::interfaces::globalVars->frametime = oldFrameTime;
		sdk::interfaces::globalVars->curtime = oldCurTime;
	}
}
