#include "hooks.hpp"
#include "../../globals.hpp"

void hooks::Initalize() noexcept
{
	paintHook.Initalize("PaintTraverse", sdk::interfaces::panel, 41, hookedFunctions::PaintTraverse);
}

void hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}

void __stdcall hookedFunctions::PaintTraverse(unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hooks::paintHook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	return original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);
}
