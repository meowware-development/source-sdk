#include "../hooks.hpp"

#include "../../../globals.hpp"



void __fastcall src::hooks::Prediction::RunCommand::HookFn(void* ecx, void* edx, BasePlayer* player, UserCmd* cmd, MoveHelper* moveHelper)
{
	using RunCommandOriginal = bool(__thiscall*)(void*, BasePlayer*, UserCmd*, MoveHelper*);
	static auto original = hook.GetOriginal<RunCommandOriginal>();

	globals::moveHelper = moveHelper;

	original(sdk::interfaces::prediction, player, cmd, moveHelper);
}