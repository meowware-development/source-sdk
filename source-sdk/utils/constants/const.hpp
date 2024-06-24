#pragma once
#include <cstdint>

namespace utils::consts {
	constexpr uint8_t pointerSize = sizeof(void*);
	constexpr const char* lastLoadedModule = "serverbrowser.dll";
	constexpr const char* prefix = "meowware > ";
}
