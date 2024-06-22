#include "hooks.hpp"
#include "../../globals.hpp"

#include "dx9/dx9.hpp"

void src::hooks::Initalize() noexcept
{
	dx9::Initialize();

	PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, PaintTraverse::PaintTraverse);
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();

	dx9::Uninitialize();
}

void __stdcall src::hooks::PaintTraverse::PaintTraverse(unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	return original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);
}
