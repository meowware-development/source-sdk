#include "../hooks.hpp"

// Currently not used

HRESULT __stdcall src::hooks::DirectX9::EndScene::HookFn(IDirect3DDevice9* device)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	return original(device);
}

HRESULT __stdcall src::hooks::DirectX9::Reset::HookFn(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	static const auto original = hook.GetOriginal<decltype(&HookFn)>();

	return original(device, pPresentationParameters);
}
