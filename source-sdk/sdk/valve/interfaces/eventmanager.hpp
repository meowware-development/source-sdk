#pragma once

class GameEventListener;
class GameEvent;

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

class GameEvent {
public:
	virtual ~GameEvent() {};
	virtual const char* GetName() const = 0;

	virtual bool  IsReliable() const = 0;
	virtual bool  IsLocal() const = 0;
	virtual bool  IsEmpty(const char* keyName) = 0;

	virtual bool  GetBool(const char* keyName, bool defaultValue = false) = 0;
	virtual int   GetInt(const char* keyName, int defaultValue = 0) = 0;
	virtual float GetFloat(const char* keyName, float defaultValue = 0.0f) = 0;
	virtual const char* GetString(const char* keyName, const char* defaultValue = "") = 0;

	virtual void SetBool(const char* keyName, bool value) = 0;
	virtual void SetInt(const char* keyName, int value) = 0;
	virtual void SetFloat(const char* keyName, float value) = 0;
	virtual void SetString(const char* keyName, const char* value) = 0;
};

class GameEventListener {
private:
	virtual void __pad0() {}
public:
	GameEventListener() = default;

	~GameEventListener() = default;

	virtual void FireGameEvent(GameEvent* event);
};