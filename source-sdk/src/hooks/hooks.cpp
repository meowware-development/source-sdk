#include "hooks.hpp"
#include "../../globals.hpp"

void src::hooks::Initalize() noexcept
{
	Panel::PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, Panel::PaintTraverse::HookFn);

	VGUIEngine::Paint::hook.Initialize("Paint", sdk::interfaces::engineVGUI, 13, VGUIEngine::Paint::HookFn);

	Surface::OnScreenSizeChanged::hook.Initialize("OnScreenSizeChanged", sdk::interfaces::surface, 111, Surface::OnScreenSizeChanged::HookFn);
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}
