#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

// C++ STD
#include <thread>
#include <chrono>

// Utils
#include "utils/utils.hpp"

// SDK
#include "sdk/sdk.hpp"

namespace globals {
	inline bool shouldUnload = false;
	inline BasePlayer* localPlayer = nullptr;
	inline MoveData* moveData = nullptr;
	inline MoveHelper* moveHelper = nullptr;
}