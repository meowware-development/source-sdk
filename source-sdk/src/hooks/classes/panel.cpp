#include "../hooks.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../sdk/valve/structures/vpanel.hpp"
#include "../../../utils/renderer/renderer.hpp"
#include "../../../utils/format/format.hpp"

#include <intrin.h>

void __fastcall src::hooks::Panel::PaintTraverse::HookFn(void* ecx, void* edx, unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	original(ecx, panelID, forceRepaint, allowForce);

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	// Draw In Game (If you pause the game, it won't render over the pause semi-transparent background)
	// Do ESP and whatnot here...
	if (panelID == sdk::interfaces::engineVGUI->GetPanel(PANEL_TOOLS)) {
		GlobalVars* globalVars = sdk::interfaces::playerInfoManager->GetGlobalVars();
		utils::renderer::Text(10.f, 25.f, utils::renderer::fonts::tahoma13outline, Color(0, 255, 255, 255), FORMAT("curtime: {}", globalVars->curtime));
		utils::renderer::Text(10.f, 40.f, utils::renderer::fonts::tahoma13outline, Color(255, 255, 0, 255), FORMAT("realtime: {}", globalVars->realtime));
		utils::renderer::Text(10.f, 55.f, utils::renderer::fonts::tahoma13outline, Color(255, 255, 0, 255), FORMAT("fps: {}", 1.0f / globalVars->frametime));
		utils::renderer::Text(10.f, 70.f, utils::renderer::fonts::tahoma13outline, Color(255, 255, 0, 255), FORMAT("map: {}", globalVars->mapname.ToCStr()));
	}
}

