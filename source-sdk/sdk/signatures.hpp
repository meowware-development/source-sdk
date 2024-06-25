#pragma once

namespace sdk::signatures {
	namespace vguimatsurface {
		// XREF "-pixel_offset_y" and "-pixel_offset_x"
		// and sig the function you find
		using StartDrawingCallback = void(__thiscall*)(void*);
		constexpr const char* StartDrawing = "55 8B EC 64 A1 00 00 00 00 6A FF 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 80";

		// XREF "Too many popups! Rendering will be bad!\n"
		// sig the latest function called
		using FinishDrawingCallback = void(__thiscall*)(void*);
		constexpr const char* FinishDrawing = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 51 56 6A";
	}

	namespace client {
		namespace clientMode {
			// Find HudProcessInput in CHLClient
			// Then find a xref to the pointer and sig a function and offset accordingly
			constexpr const char* sig = "56 8B F1 8B 0D ?? ?? ?? ?? 8B 01 8B 40 64";
			constexpr int offset = 5;
		}
	}
}