#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

// C++ STD
#include <thread>
#include <chrono>

// This is the last module that is being loaded by pretty much every source game.
#define LAST_LOADED_MODULE "serverbrowser.dll"

// Utils
#include "utils/debug/debug.hpp"

namespace globals {
	bool shouldUnload = false;
}