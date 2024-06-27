#include "../hooks.hpp"

#include "../../../sdk/signatures.hpp"
#include "../../../sdk/interfaces/interfaces.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/renderer/renderer.hpp"

void __fastcall src::hooks::VGUIEngine::Paint::HookFn(void* ecx, void* edx, int paintMode)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	original(ecx, edx, paintMode);

	static auto StartDrawing = utils::memory::PatternScan(utils::memory::GetModule("vguimatsurface.dll"), sdk::signatures::vguimatsurface::StartDrawing).Cast<sdk::signatures::vguimatsurface::StartDrawingCallback>();
	static auto FinishDrawing = utils::memory::PatternScan(utils::memory::GetModule("vguimatsurface.dll"), sdk::signatures::vguimatsurface::FinishDrawing).Cast<sdk::signatures::vguimatsurface::FinishDrawingCallback>();

	StartDrawing(sdk::interfaces::surface);

	FinishDrawing(sdk::interfaces::surface);
}