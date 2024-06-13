#pragma once
#include "vmthook/vmthook.hpp"

namespace hooks {
	void Initalize() noexcept;
	void Uninitalize() noexcept;

	inline VMTHook paintHook{};
}

namespace hookedFunctions {
	void __stdcall PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce);
}