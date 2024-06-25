#pragma once
#include <cstdint>

class ClientNetworkable;
class ClientEntity;
class ClientUnknown;

class ClientEntityList {
public:
	// Get IClientNetworkable interface for specified entity
	virtual ClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual ClientNetworkable* GetClientNetworkableFromHandle(uintptr_t hEnt) = 0;
	virtual ClientUnknown* GetClientUnknownFromHandle(uintptr_t hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual ClientEntity* GetClientEntity(int entnum) = 0;
	virtual ClientEntity* GetClientEntityFromHandle(uintptr_t hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};