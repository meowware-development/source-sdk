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
	
	original(sdk::interfaces::panel, panelID, forceRepaint, allowForce);


	if (!forceRepaint || !allowForce)
		return;

	if (std::string_view(panel->GetName()) == "FocusOverlayPanel") {
		static auto originalPanel = panelID;
		if (panelID != originalPanel)
			return;

		utils::renderer::FilledRectangle(0, 0, 100, 100, Color(100, 100, 100));
		utils::renderer::Rectangle(300, 300, 150, 150, Color(255, 255, 255));
		utils::renderer::Text(0, 120, utils::renderer::fonts::tahoma13, Color(255, 255, 255), "[meowware]");
	}
}

