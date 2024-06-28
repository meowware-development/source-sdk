#pragma once
#include "baseentity.hpp"

class BasePlayer : public BaseEntity {
public:
	NETVAR(int, Flags, DT_BasePlayer, m_fFlags);
	NETVAR(int, TickBase, DT_BasePlayer, m_nTickBase);
	NETVAR(int, Health, DT_BasePlayer, m_iHealth);
	NETVAR(bool, LifeState, DT_BasePlayer, m_lifeState);
	NETVAR(void*, ObserverTarget, DT_BasePlayer, m_iObserverTarget);
	NETVAR(void*, ObserverMode, DT_BasePlayer, m_iObserverMode);
	NETVAR(void*, ActiveWeapon, DT_BasePlayer, m_hActiveWeapon);
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

	bool IsAlive();

	void SetLocalViewangles(Vector3 newAngle);
	void PreThink();
	void Think();
	void PostThink();

	void UpdateButtonStates(int buttonMask);
};