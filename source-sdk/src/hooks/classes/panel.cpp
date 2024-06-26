#include "../hooks.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../sdk/valve/structures/vpanel.hpp"
#include "../../../utils/renderer/renderer.hpp"
#include "../../../utils/format/format.hpp"
#include "../../../sdk/sdk.hpp"
#include "../../features/esp.hpp"


void __fastcall src::hooks::Panel::PaintTraverse::HookFn(void* ecx, void* edx, unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);

	if (!forceRepaint || !allowForce)
		return;

	// Always focused panel, always bright
	static int FocusOverlayPanel = 0;

	// Reacts to in-game panels by dimming (ex. when console is up it gets dimmer)
	static int EngineTools = 0;

	if (FocusOverlayPanel == 0) {
		if (std::string_view(panel->GetName()) == "FocusOverlayPanel") {
			FocusOverlayPanel = panelID;
		}
	}

	if (EngineTools == 0) {
		if (std::string_view(panel->GetName()) == "Engine Tools") {
			EngineTools = panelID;
		}
	}

	// A switch statement doesn't work here since the variables are static
	if (panelID == FocusOverlayPanel) {
		utils::renderer::Text(20, 20, utils::renderer::fonts::tahoma13, Color(255, 255, 255), "[source-sdk] Counter-Strike: Source");

		src::features::Run2D();
	}
	else if (panelID == EngineTools) {
		GlobalVars* globalVars = sdk::interfaces::playerInfoManager->GetGlobalVars();

		utils::renderer::Text(20, 35, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("curtime: {:.2f}", globalVars->curtime));
		utils::renderer::Text(20, 50, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("realtime: {:.2f}", globalVars->realtime));
		utils::renderer::Text(20, 65, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("map: {}", globalVars->mapname.ToCStr()));
	}
}

