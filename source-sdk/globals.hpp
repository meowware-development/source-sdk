#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

// C++ STD
#include <thread>
#include <chrono>

// This is the last module that is being loaded by pretty much every source game.
static constexpr const char* LAST_LOADED_MODULE = "notepad.exe";

// Utils
#include "utils/debug/debug.hpp"

namespace globals {
	inline bool shouldUnload = false;
}