#include "../hooks.hpp"

#include "../../../utils/renderer/renderer.hpp"
#include "../../../sdk/interfaces/interfaces.hpp"

void __fastcall src::hooks::Surface::OnScreenSizeChanged::HookFn(void* thisptr, void* edx, int nOldWidth, int nOldHeight)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	// Firstly, call the original to let the game handle the resolution change
	original(sdk::interfaces::surface, edx, nOldWidth, nOldHeight);

	// Get the new screen size, and initialize fonts again
	utils::renderer::Initialize();
}