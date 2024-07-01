#pragma once
#include <vector>
#include <memory>

#include "../valve/interfaces/eventmanager.hpp"

namespace sdk::events {
	inline GameEventListener* eventListener = new GameEventListener();

	inline std::vector<const char*> events = {
		"player_hurt"

		// Add any event here
	};

	void Initialize();
	void Uninitialize();
}