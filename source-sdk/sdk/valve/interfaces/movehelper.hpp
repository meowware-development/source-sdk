#pragma once
#include "../../math/vector.hpp"
#include "../structures/trace.hpp"

class MoveHelper
{
public:

	// Methods associated with a particular entity
	virtual	char const* GetName(unsigned long handle) const = 0;

	// Adds the trace result to touch list, if contact is not already in list.
	virtual void	ResetTouchList(void) = 0;
	virtual bool	AddToTouched(const GameTrace& tr, const Vector3& impactvelocity) = 0;
	virtual void	ProcessImpacts(void) = 0;

	// Numbered line printf
	virtual void	Con_NPrintf(int idx, char const* fmt, ...) = 0;

	// These have separate server vs client impementations
	virtual void	StartSound(const Vector3& origin, int channel, char const* sample, float volume, int soundlevel, int fFlags, int pitch) = 0;
	virtual void	StartSound(const Vector3& origin, const char* soundname) = 0;
	virtual void	PlaybackEventFull(int flags, int clientindex, unsigned short eventindex, float delay, Vector3& origin, Vector3& angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2) = 0;

	// Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
	virtual bool	PlayerFallingDamage(void) = 0;

	// Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
	virtual void	PlayerSetAnimation(int playerAnim) = 0;

	virtual void* GetSurfaceProps(void) = 0;

	virtual bool IsWorldEntity(const uintptr_t& handle) = 0;

	// Clients shouldn't call delete directly
	virtual			~MoveHelper() {}
};