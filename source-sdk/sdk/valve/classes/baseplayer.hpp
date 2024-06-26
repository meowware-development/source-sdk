#pragma once
#include "baseentity.hpp"

struct UserCmd;

class BasePlayer : public BaseEntity {
public:
	NETVAR(int, Flags, DT_BasePlayer, m_fFlags);
	NETVAR(int, TickBase, DT_BasePlayer, m_nTickBase);
	NETVAR(int, Health, DT_BasePlayer, m_iHealth);
	NETVAR(bool, LifeState, DT_BasePlayer, m_lifeState);
	NETVAR(void*, ObserverTarget, DT_BasePlayer, m_iObserverTarget);
	NETVAR(void*, ObserverMode, DT_BasePlayer, m_iObserverMode);
	NETVAR(uintptr_t, ActiveWeapon, DT_BasePlayer, m_hActiveWeapon);
	NETVAR(void*, Weapons, DT_BasePlayer, m_hMyWeapons);
	NETVAR(void*, ZoomOwner, DT_BasePlayer, m_hZoomOwner);
	NETVAR(void*, LastWeapon, DT_BasePlayer, m_hLastWeapon);
	NETVAR(int, DefaultFOV, DT_BasePlayer, m_iDefaultFOV);
	NETVAR(int, FOVStart, DT_BasePlayer, m_iFOVStart);
	NETVAR(int, FOV, DT_BasePlayer, m_iFOV);
	NETVAR(Vector3, Velocity, DT_BasePlayer, m_vecVelocity[0]);
	NETVAR(Vector3, ViewOffset, DT_BasePlayer, m_vecViewOffset[0]);
	NETVAR(float, MaxSpeed, DT_BasePlayer, m_flMaxspeed);
	NETVAR(float, DeathTime, DT_BasePlayer, m_flDeathTime);
	NETVAR(bool, GlowEnabled, DT_BasePlayer, m_bGlowEnabled);
	NETVAR(bool, Local, DT_BasePlayer, m_Local);
	NETVAR(void*, GroundEntity, DT_BasePlayer, m_hGroundEntity);

	bool IsAlive();

	void SetLocalViewangles(Vector3 newAngle);
	void PreThink();
	void Think();
	void PostThink();

	int GetNextThinkTick();
	void SetNextThinkTick(float nextTick = -1.0f);

	void UpdateButtonStates(int buttonMask);
	void SetCurrentCommand(UserCmd* command);
	void SelectItem(const char* name, int subType = 0);
	void SetImpulse(int impulse);

	void SetCollisionBounds(Vector3* min, Vector3* max);

	int GetSequence();
	void SetSequence(int newSequence);

	void StudioFrameAdvance();

	int GetSimulationTick();
	void SetSimulationTick(int newSimTick);

	struct CommandContext* GetCommandContext();
};