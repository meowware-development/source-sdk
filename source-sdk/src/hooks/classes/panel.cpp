#include "../hooks.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../sdk/valve/structures/vpanel.hpp"
#include "../../../utils/renderer/renderer.hpp"

void __stdcall src::hooks::Panel::PaintTraverse::HookFn(unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	if (!strcmp(panel->GetName(), "FocusOverlayPanel")) {
		utils::renderer::FilledRectangle(200.f, 400.f, 500.f, 500.f, Color(100, 0, 200));
		utils::renderer::Text(10.f, 10.f, utils::renderer::fonts::tahoma13, Color(255, 255, 255, 255), "[source-sdk]");
	}

	return original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);
}

