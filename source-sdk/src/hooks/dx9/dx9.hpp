#pragma once
#include "../vmthook/vmthook.hpp"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace src::hooks::dx9 {
	void Initialize();

	namespace EndScene {
		inline VMTHook hook;
		HRESULT __stdcall EndScene(IDirect3DDevice9* device);
	}

	namespace Reset {
		inline VMTHook hook;
		HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
	}
}