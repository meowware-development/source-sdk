#pragma once
#include "vmthook/vmthook.hpp"

#include <d3d9.h>

namespace src::hooks {
	void Initalize() noexcept;
	void Uninitalize() noexcept;

	namespace Panel {
		namespace PaintTraverse {
			inline VMTHook hook;
			void __stdcall PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce);
		}
	}

	namespace DirectX9 {
		namespace EndScene {
			inline VMTHook hook;
			HRESULT __stdcall EndScene(IDirect3DDevice9* device);
		}

		namespace Reset {
			inline VMTHook hook;
			HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
		}
	}
}
