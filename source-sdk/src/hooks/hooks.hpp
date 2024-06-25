#pragma once
#include "vmthook/vmthook.hpp"

#include <d3d9.h>

namespace src::hooks {
	void Initalize() noexcept;
	void Uninitalize() noexcept;

	namespace Panel {
		namespace PaintTraverse {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, unsigned int panel, bool forceRepaint, bool allowForce);
		}
	}

	namespace VGUIEngine {
		namespace Paint {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, int paintMode);
		}
	}

	namespace DirectX9 {
		namespace EndScene {
			inline VMTHook hook;
			HRESULT __stdcall HookFn(IDirect3DDevice9* device);
		}

		namespace Reset {
			inline VMTHook hook;
			HRESULT __stdcall HookFn(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
		}
	}

	namespace Surface {
		namespace OnScreenSizeChanged {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, int nOldWidth, int nOldHeight);
		}
	}
}
