#pragma once
#include "../../math/vector.hpp"
#include "../enums/sourcedefs.hpp"

enum class ECritType
{
	CRIT_NONE = 0,
	CRIT_MINI,
	CRIT_FULL,
};

struct TakeDamageInfo {
	Vector3			m_vecDamageForce;
	Vector3			m_vecDamagePosition;
	Vector3			m_vecReportedPosition;	// Position players are told damage is coming from
	EHANDLE			m_hInflictor;
	EHANDLE			m_hAttacker;
	EHANDLE			m_hWeapon;
	float			m_flDamage;
	float			m_flMaxDamage;
	float			m_flBaseDamage;			// The damage amount before skill leve adjustments are made. Used to get uniform damage forces.
	int				m_bitsDamageType;
	int				m_iDamageCustom;
	int				m_iDamageStats;
	int				m_iAmmoType;			// AmmoType of the weapon used to cause this damage, if any
	int				m_iDamagedOtherPlayers;
	int				m_iPlayerPenetrationCount;
	float			m_flDamageBonus;		// Anything that increases damage (crit) - store the delta
	EHANDLE			m_hDamageBonusProvider;	// Who gave us the ability to do extra damage?
	bool			m_bForceFriendlyFire;	// Ideally this would be a dmg type, but we can't add more

	float			m_flDamageForForce;

	ECritType		m_eCritType;
};