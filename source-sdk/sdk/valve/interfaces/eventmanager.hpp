#pragma once
#include "../structures/event.hpp"

class GameEventManager {
public:
	virtual ~GameEventManager(void) {};

	// load game event descriptions from a file eg "resource\gameevents.res"
	virtual int LoadEventsFromFile(const char* filename) = 0;

	// removes all and anything
	virtual void  Reset() = 0;

	// adds a listener for a particular event
	virtual bool AddListener(GameEventListener* listener, const char* name, bool bServerSide) = 0;

	// returns true if this listener is listens to given event
	virtual bool FindListener(GameEventListener* listener, const char* name) = 0;

	// removes a listener 
	virtual void RemoveListener(GameEventListener* listener) = 0;

	// create an event by name, but doesn't fire it. returns NULL is event is not
	// known or no listener is registered for it. bForce forces the creation even if no listener is active
	virtual GameEvent* CreateEvent(const char* name, bool bForce = false) = 0;

	// fires a server event created earlier, if bDontBroadcast is set, event is not send to clients
	virtual bool FireEvent(GameEvent* event, bool bDontBroadcast = false) = 0;
};