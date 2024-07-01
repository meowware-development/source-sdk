#include "../hooks.hpp"

#include "../../../utils/renderer/renderer.hpp"
#include "../../../sdk/interfaces/interfaces.hpp"

// Meant for handling resolution change
void __fastcall src::hooks::Surface::OnScreenSizeChanged::HookFn(void* thisptr, void* edx, int nOldWidth, int nOldHeight)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	original(sdk::interfaces::surface, edx, nOldWidth, nOldHeight);

	// Initialize the renderer (fonts, screensize) again
	utils::renderer::Initialize();
}