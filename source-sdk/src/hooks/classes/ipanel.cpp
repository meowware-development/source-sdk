#include "../hooks.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../sdk/valve/structures/vpanel.hpp"
#include "../../../utils/renderer/renderer.hpp"
#include "../../../utils/debug/debug.hpp"

void __stdcall src::hooks::Panel::PaintTraverse::HookFn(unsigned int panelID, bool forceRepaint, bool allowForce)
{
	static const auto original = hook.GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>();

	original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);

	VPanel* panel = reinterpret_cast<VPanel*>(panelID);

	const char* panelName = panel->GetName();

	static unsigned int FocusOverlayPanel = 0;

	if (!FocusOverlayPanel) {
		if (panelName[0] == 'F' && panelName[2] == 'c')
			FocusOverlayPanel = panelID;
	}
	else if (panelID == FocusOverlayPanel) {
		utils::renderer::Text(10.f, 10.f, utils::renderer::fonts::tahoma13, Color(255, 255, 255, 255), "[source-sdk]");
	}
}

