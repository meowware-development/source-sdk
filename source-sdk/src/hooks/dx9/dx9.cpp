#include "dx9.hpp"

#include <exception>
#include "../../../utils/format/format.hpp"

void src::hooks::dx9::Initialize()
{
	// Create Device
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// Probably won't ever happen
	if (!d3d)
		return;

	// Get game window
	HWND foregroundWindow = GetForegroundWindow();

	// D3D Parameters for the device
	D3DPRESENT_PARAMETERS param = { 0 };
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.hDeviceWindow = foregroundWindow;
	param.Windowed = true;

	HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, foregroundWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &param, &device);

	if (FAILED(result) || !device) {
		// Probably won't ever happen
		d3d->Release();
		return;
	}

	// Hook EndScene and Reset, Indexes can be found in d3d9.h
	EndScene::hook.Initialize("EndScene", device, 42, EndScene::EndScene);
	Reset::hook.Initialize("Reset", device, 16, Reset::Reset);
}

void src::hooks::dx9::Uninitialize()
{
	if (device)
		device->Release();

	if (d3d)
		d3d->Release();
}

HRESULT __stdcall src::hooks::dx9::EndScene::EndScene(IDirect3DDevice9* device)
{
	static const auto original = hook.GetOriginal<decltype(&EndScene)>();

	return original(device);
}

HRESULT __stdcall src::hooks::dx9::Reset::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	static const auto original = hook.GetOriginal<decltype(&Reset)>();

	return original(device, pPresentationParameters);
}
