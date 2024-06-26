#include "eventlistener.hpp"

#include "../../../sdk/interfaces/interfaces.hpp"

#include "../../../utils/debug/debug.hpp"
#include "../../../utils/hash/fnv1a.hpp"

void GameEventListener::FireGameEvent(GameEvent* event) {
	switch (utils::hash::fnv1a::hash32(event->GetName()))
	{
	case utils::hash::fnv1a::hash32("player_hurt"): {
		LOG(DebugLevel::ERR, "Player hurt!");
		break;
	}
	}
}

void sdk::events::Initialize() {
	for (const auto& event : events) {
		LOG(DebugLevel::OK, "Added event {}..", event);
		sdk::interfaces::gameEventManager->AddListener(eventListener, event, false);
	}

	LOG(DebugLevel::OK, "Initialized the event listener!");
}

void sdk::events::Uninitialize() {
	sdk::interfaces::gameEventManager->RemoveListener(eventListener);
	delete eventListener;
}
