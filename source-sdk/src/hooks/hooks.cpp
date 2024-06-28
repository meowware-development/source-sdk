#include "hooks.hpp"
#include "../../globals.hpp"

void src::hooks::Initalize() noexcept
{
	Panel::PaintTraverse::hook.Initialize("PaintTraverse", sdk::interfaces::panel, 41, Panel::PaintTraverse::HookFn);

	Client::HudUpdate::hook.Initialize("HudUpdate", sdk::interfaces::client, 11, Client::HudUpdate::HookFn);
	ClientMode::CreateMove::hook.Initialize("CreateMove", sdk::interfaces::clientMode, 21, ClientMode::CreateMove::HookFn);

	Surface::OnScreenSizeChanged::hook.Initialize("OnScreenSizeChanged", sdk::interfaces::surface, 111, Surface::OnScreenSizeChanged::HookFn);

	Prediction::RunCommand::hook.Initialize("RunCommand", sdk::interfaces::prediction, 17, Prediction::RunCommand::HookFn);

	LOG(DebugLevel::OK, "Initialized hooks!");
}

void src::hooks::Uninitalize() noexcept
{
	VMTHook::Uninitialize();
}