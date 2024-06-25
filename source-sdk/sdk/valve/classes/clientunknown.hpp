#pragma once

class ClientNetworkable;
class ClientEntity;
class BaseEntity;
class ClientRenderable;

class ClientUnknown {
private: // Stuff from IHandleEntity
	virtual void __pad0() = 0;
	virtual void __pad1() = 0;
	virtual void __pad2() = 0;
public:
	virtual void* GetCollideable() = 0;
	virtual ClientNetworkable* GetClientNetworkable() = 0;
	virtual ClientRenderable* GetClientRenderable() = 0;
	virtual ClientEntity* GetClientEntity() = 0;
	virtual BaseEntity* GetBaseEntity() = 0;
};