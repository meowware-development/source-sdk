#pragma once
#include "handleentity.hpp"

class ClientNetworkable;
class ClientEntity;
class BaseEntity;
class ClientRenderable;
class Collideable;

class ClientUnknown : public HandleEntity {
public:
	virtual Collideable* GetCollideable() = 0;
	virtual ClientNetworkable* GetClientNetworkable() = 0;
	virtual ClientRenderable* GetClientRenderable() = 0;
	virtual ClientEntity* GetClientEntity() = 0;
	virtual BaseEntity* GetBaseEntity() = 0;
};