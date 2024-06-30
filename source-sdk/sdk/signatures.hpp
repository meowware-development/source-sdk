#pragma once

namespace sdk::signatures {
	namespace client {
		namespace clientMode {
			// Find HudProcessInput in CHLClient
			// Then find a xref to the pointer and sig a function and offset accordingly
			constexpr const char* sig = "56 8B F1 8B 0D ?? ?? ?? ?? 8B 01 8B 40 64";
			constexpr int offset = 5;
		}

		namespace C_BaseEntity {
			//
			namespace MoveType {
				constexpr const char* sig = "80 B8 ?? ?? ?? ?? ?? A1";
				constexpr int offset = 2;
			}
		}
	}
}