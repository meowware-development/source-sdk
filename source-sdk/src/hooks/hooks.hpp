#pragma once
#include "vmthook/vmthook.hpp"

class BasePlayer;
struct UserCmd;
class MoveHelper;

namespace src::hooks {
	void Initalize() noexcept;
	void Uninitalize() noexcept;

	namespace Panel {
		namespace PaintTraverse {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, unsigned int panel, bool forceRepaint, bool allowForce);
		}
	}

	namespace Surface {
		namespace OnScreenSizeChanged {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, int nOldWidth, int nOldHeight);
		}
	}

	namespace ClientMode {
		namespace CreateMove {
			inline VMTHook hook;
			bool __stdcall HookFn(float time, void* usercmd);
		}
	}

	namespace Client {
		namespace HudUpdate {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, bool active);
		}
	}

	namespace Prediction {
		namespace RunCommand {
			inline VMTHook hook;
			void __fastcall HookFn(void* ecx, void* edx, BasePlayer* player, UserCmd* cmd, MoveHelper* moveHelper);
		}
	}
}
