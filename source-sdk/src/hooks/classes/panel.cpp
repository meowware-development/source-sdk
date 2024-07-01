#include "../hooks.hpp"

#include "../../../sdk/sdk.hpp"

#include "../../../utils/renderer/renderer.hpp"
#include "../../../utils/format/format.hpp"

#include "../../features/esp.hpp"
#include "../../../globals.hpp"

// Meant for drawing (both in game and in menu)
void __fastcall src::hooks::Panel::PaintTraverse::HookFn(void* thisptr, void* edx, unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	original(sdk::interfaces::panel, edx, panelID, forceRepaint, allowForce);

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
		// Draw stuff like menu, watermark etc here
		utils::renderer::Text(20, 20, utils::renderer::fonts::tahoma13, Color(255, 255, 255), "[source-sdk] Counter-Strike: Source");
	}
	else if (panelID == EngineTools) {
		// Draw anything related to esp here
		utils::renderer::Text(20, 35, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("curtime: {:.2f}", sdk::interfaces::globalVars->curtime));
		utils::renderer::Text(20, 50, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("realtime: {:.2f}", sdk::interfaces::globalVars->realtime));
		utils::renderer::Text(20, 65, utils::renderer::fonts::tahoma13, Color(255, 255, 255), FORMAT("map: {}", sdk::interfaces::globalVars->mapname.ToCStr()));
		utils::renderer::Text(20, 80, utils::renderer::fonts::tahoma13, Color(0, 255, 0), FORMAT("Pre pred (current): {:.2f},{:.2f},{:.2f}", globals::prePredPosition.x, globals::prePredPosition.y,
																								 globals::prePredPosition.z));
		utils::renderer::Text(20, 95, utils::renderer::fonts::tahoma13, Color(255, 0, 0), FORMAT("Post pred (1 tick ahead): {:.2f},{:.2f},{:.2f}", globals::postPredPosition.x, globals::postPredPosition.y,
																								 globals::postPredPosition.z));
		const Color matchColor = globals::prePredPosition == globals::postPredPosition ? Color(255, 0, 0) : Color(0, 255, 0);
		utils::renderer::Text(20, 110, utils::renderer::fonts::tahoma13, matchColor, FORMAT("Matches? {}", globals::prePredPosition == globals::postPredPosition));

		src::features::esp::Run();
	}
}

