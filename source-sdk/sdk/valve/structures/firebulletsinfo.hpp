#pragma once
#include "../../math/vector.hpp"

enum FireBulletsFlag
{
	FIRE_BULLETS_FIRST_SHOT_ACCURATE = 0x1,		// Pop the first shot with perfect accuracy
	FIRE_BULLETS_DONT_HIT_UNDERWATER = 0x2,		// If the shot hits its target underwater, don't damage it
	FIRE_BULLETS_ALLOW_WATER_SURFACE_IMPACTS = 0x4,	// If the shot hits water surface, still call DoImpactEffect
	FIRE_BULLETS_TEMPORARY_DANGER_SOUND = 0x8,		// Danger sounds added from this impact can be stomped immediately if another is queued
};

class BaseEntiy;

struct FireBulletsInfo
{
	FireBulletsInfo()
	{
		m_iShots = 1;
		m_vecSpread.Init(0, 0, 0);
		m_flDistance = 8192;
		m_iTracerFreq = 4;
		m_flDamage = 0;
		m_iPlayerDamage = 0;
		m_pAttacker = NULL;
		m_nFlags = 0;
		m_pAdditionalIgnoreEnt = NULL;
		m_flDamageForceScale = 1.0f;

#ifdef _DEBUG
		m_iAmmoType = -1;
		m_vecSrc.Init(0, 0, 0); // 0 is not NaN but oh well..
		m_vecDirShooting.Init(0, 0, 0);
#endif
		m_bPrimaryAttack = true;
		m_bUseServerRandomSeed = false;
	}

	FireBulletsInfo(int nShots, const Vector3& vecSrc, const Vector3& vecDir, const Vector3& vecSpread, float flDistance, int nAmmoType, bool bPrimaryAttack = true)
	{
		m_iShots = nShots;
		m_vecSrc = vecSrc;
		m_vecDirShooting = vecDir;
		m_vecSpread = vecSpread;
		m_flDistance = flDistance;
		m_iAmmoType = nAmmoType;
		m_iTracerFreq = 4;
		m_flDamage = 0;
		m_iPlayerDamage = 0;
		m_pAttacker = NULL;
		m_nFlags = 0;
		m_pAdditionalIgnoreEnt = NULL;
		m_flDamageForceScale = 1.0f;
		m_bPrimaryAttack = bPrimaryAttack;
		m_bUseServerRandomSeed = false;
	}

	int m_iShots;
	Vector3 m_vecSrc;
	Vector3 m_vecDirShooting;
	Vector3 m_vecSpread;
	float m_flDistance;
	int m_iAmmoType;
	int m_iTracerFreq;
	float m_flDamage;
	int m_iPlayerDamage;	// Damage to be used instead of m_flDamage if we hit a player
	int m_nFlags;			// See FireBulletsFlags_t
	float m_flDamageForceScale;
	BaseEntiy* m_pAttacker;
	BaseEntiy* m_pAdditionalIgnoreEnt;
	bool m_bPrimaryAttack;
	bool m_bUseServerRandomSeed;
};