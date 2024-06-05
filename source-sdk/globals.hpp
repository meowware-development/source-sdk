#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

// C++ STD
#include <thread>
#include <chrono>

// Utils
#include "utils/debug/debug.hpp"
#include "utils/format/format.hpp"
#include "utils/memory/memory.hpp"
#include "utils/constants/const.hpp"

namespace globals {
	inline bool shouldUnload = false;
}