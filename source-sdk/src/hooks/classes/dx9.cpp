#pragma once

#include "../hooks.hpp"

// Currently not used

HRESULT __stdcall src::hooks::DirectX9::EndScene::EndScene(IDirect3DDevice9* device)
{
	static const auto original = hook.GetOriginal<decltype(&EndScene)>();

	return original(device);
}

HRESULT __stdcall src::hooks::DirectX9::Reset::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	static const auto original = hook.GetOriginal<decltype(&Reset)>();

	return original(device, pPresentationParameters);
}
