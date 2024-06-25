#include "hooks.hpp"
#include "../../globals.hpp"

void src::hooks::Initalize() noexcept
{
	Panel::PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, Panel::PaintTraverse::HookFn);

	// Uncomment this if you want to hook VGuiEngine->Paint. Could be useful if you only want to render when the console isn't open.
	// VGUIEngine::Paint::hook.Initialize("Paint", sdk::interfaces::engineVGUI, 13, VGUIEngine::Paint::HookFn);

	ClientMode::CreateMove::hook.Initialize("CreateMove", sdk::interfaces::clientMode, 21, ClientMode::CreateMove::HookFn);

	Surface::OnScreenSizeChanged::hook.Initialize("OnScreenSizeChanged", sdk::interfaces::surface, 111, Surface::OnScreenSizeChanged::HookFn);

	LOG(DebugLevel::OK, "Initialized hooks!");
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}
