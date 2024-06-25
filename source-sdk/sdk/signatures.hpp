#pragma once

namespace sdk::signatures {
	namespace shaderapidx9 {
		// xref "mat_queue_mode"
		// https://prnt.sc/cyZiFNTyWiMn
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3d9-createdevice
		namespace directx9 {
			constexpr const char* sig = "55 8B EC 83 EC ?? A1 ?? ?? ?? ?? 8D 55";
			constexpr int offset = 0x7;
		}
	}

	namespace client {
		namespace globalvars {
			constexpr const char* sig = "A1 ?? ?? ?? ?? 56 8B F1 FF 70";
			constexpr int offset = 1;
		}
	}
}