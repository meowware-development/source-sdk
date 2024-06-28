#include "../hooks.hpp"

#include "../../../utils/renderer/renderer.hpp"
#include "../../../sdk/interfaces/interfaces.hpp"

// Under the hood, this function is probably being called on directx9 device Reset
void __fastcall src::hooks::Surface::OnScreenSizeChanged::HookFn(void* ecx, void* edx, int nOldWidth, int nOldHeight)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	// Firstly, call the original to let the game handle the resolution change
	original(ecx, edx, nOldWidth, nOldHeight);

	// Get the new screen size, and initialize fonts again
	utils::renderer::Initialize();
}