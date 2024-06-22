#pragma once
#include "vmthook/vmthook.hpp"

namespace src::hooks {
	void Initalize() noexcept;
	void Uninitalize() noexcept;

	namespace PaintTraverse {
		inline VMTHook hook;
		void __stdcall PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce);
	}
}
