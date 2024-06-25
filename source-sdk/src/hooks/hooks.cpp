#include "hooks.hpp"
#include "../../globals.hpp"

void src::hooks::Initalize() noexcept
{
	Panel::PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, Panel::PaintTraverse::HookFn);

	VGUIEngine::Paint::hook.Initialize("Paint", sdk::interfaces::engineVGUI, 13, VGUIEngine::Paint::HookFn);

	DirectX9::EndScene::hook.Initialize("EndScene", sdk::interfaces::directx9, 42, DirectX9::EndScene::HookFn);
	DirectX9::Reset::hook.Initialize("Reset", sdk::interfaces::directx9, 16, DirectX9::Reset::HookFn);

	ClientMode::CreateMove::hook.Initialize("CreateMove", sdk::interfaces::clientMode, 21, ClientMode::CreateMove::HookFn);

	Surface::OnScreenSizeChanged::hook.Initialize("OnScreenSizeChanged", sdk::interfaces::surface, 111, Surface::OnScreenSizeChanged::HookFn);
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}
