#include "../hooks.hpp"

#include "../../../globals.hpp"

void __fastcall src::hooks::Prediction::RunCommand::HookFn(void* thisptr, void* edx, BasePlayer* player, UserCmd* cmd, MoveHelper* moveHelper)
{
	static auto original = hook.GetOriginal<decltype(&HookFn)>();

	//globals::prediction::moveHelper = moveHelper;

	original(sdk::interfaces::prediction, edx, player, cmd, moveHelper);
}