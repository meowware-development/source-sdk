#include "dx9.hpp"

#include <exception>
#include "../../../utils/format/format.hpp"
#include "../../../utils/memory/memory.hpp"

void src::hooks::dx9::Initialize()
{
	IDirect3D9* d3d = nullptr;
	IDirect3DDevice9* device = nullptr;

	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"source-sdk";
	windowClass.hIconSm = NULL;

	RegisterClassExW(&windowClass);

	HWND window = CreateWindow(windowClass.lpszClassName, L"source-sdk", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

	// Get D3D9 module
	const auto d3d9 = utils::memory::GetModule("d3d9.dll");

	// Get Create proceedure from inside the module
	void* Direct3DCreate9;
	if ((Direct3DCreate9 = GetProcAddress(reinterpret_cast<HMODULE>(d3d9), "Direct3DCreate9")) == NULL) {
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return;
	}

	// Create the device
	if ((d3d = ((IDirect3D9 * (__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION)) == NULL) {
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return;
	}

	D3DDISPLAYMODE displayMode = { 0 };

	// Display mode
	if (FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode))) {
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return;
	}

	// D3D Parameters for the device
	D3DPRESENT_PARAMETERS params;
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = displayMode.Format;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device);

	if (FAILED(result) || !device) {
		// Probably won't ever happen
		d3d->Release();
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return;
	}

	// Hook EndScene and Reset, Indexes can be found in d3d9.h
	EndScene::hook.Initialize("EndScene", device, 42, EndScene::EndScene);
	Reset::hook.Initialize("Reset", device, 16, Reset::Reset);

	d3d->Release();
	d3d = NULL;

	device->Release();
	device = NULL;

	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
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
