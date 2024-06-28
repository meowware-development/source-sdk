#include "../hooks.hpp"

#include "../../../sdk/sdk.hpp"

#include "../../../utils/renderer/renderer.hpp"
#include "../../../utils/format/format.hpp"

#include "../../features/esp.hpp"

void __fastcall src::hooks::Panel::PaintTraverse::HookFn(void* ecx, void* edx, unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);

	if (!forceRepaint || !allowForce)
		return;

	// Meant for drawing over EVERYTHING (including pause menu, console, etc)
	static int FocusOverlayPanel = 0;

	// Meant for drawing only in the game (while not paused), for example ESP
	static int EngineTools = 0;

	// Cache Panel ID to check against later
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

	// A switch statement doesn't work here since the variables are not constant
	if (panelID == FocusOverlayPanel) {
		utils::renderer::Text(20, 20, utils::renderer::fonts::tahoma13, Color(255, 255, 255), "[source-sdk] Counter-Strike: Source");
	}
	else if (panelID == EngineTools) {
		GlobalVars* globalVars = sdk::interfaces::playerInfoManager->GetGlobalVars();

		utils::renderer::Text(20, 35, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("curtime: {:.2f}", globalVars->curtime));
		utils::renderer::Text(20, 50, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("realtime: {:.2f}", globalVars->realtime));
		utils::renderer::Text(20, 65, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("map: {}", globalVars->mapname.ToCStr()));
		utils::renderer::Text(20, 80, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("framecount: {}", globalVars->framecount));
		src::features::esp::Run();
	}
}

