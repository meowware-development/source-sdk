#pragma once
#include "clientnetworkable.hpp"
#include "clientrenderable.hpp"
#include "clientunknown.hpp"
#include "clientthinkable.hpp"

#include "../netvars/netvar.hpp"

class ClientEntity : public ClientUnknown, public ClientRenderable, public ClientNetworkable, public ClientThinkable
{
public:
	template <typename Type>
	Type* As() { return reinterpret_cast<Type*>(this); }

	// Delete yourself.
	virtual void			Release(void) = 0;

	// Network origin + angles
	virtual const Vector3& GetAbsOrigin(void) const = 0;
	virtual const Vector3& GetAbsAngles(void) const = 0;

	virtual void* GetMouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			GetSoundSpatialization(void* info) = 0;
};
