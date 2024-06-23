#include "hooks.hpp"
#include "../../globals.hpp"

void src::hooks::Initalize() noexcept
{
	Panel::PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, Panel::PaintTraverse::PaintTraverse);

	DirectX9::EndScene::hook.Initialize("EndScene", sdk::interfaces::directx9, 42, DirectX9::EndScene::EndScene);
	DirectX9::Reset::hook.Initialize("Reset", sdk::interfaces::directx9, 16, DirectX9::Reset::Reset);
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}

void __stdcall src::hooks::Panel::PaintTraverse::PaintTraverse(unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	return original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);
}
