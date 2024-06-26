#pragma once

struct GameEvent {
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