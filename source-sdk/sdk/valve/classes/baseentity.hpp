#pragma once
#include "cliententity.hpp"

#include "../../math/vector.hpp"

#include "../structures/firebulletsinfo.hpp"
#include "../structures/takedamageinfo.hpp"
#include "../structures/studio.hpp"
#include "collideable.hpp"

#include "../misc/color.hpp"
#include "../misc/entity.hpp"

#include "../netvars/netvar.hpp"

struct Model;

class BaseEntity : public ClientEntity {
public:
	static BaseEntity* GetLocalEntity();
	int GetSolidFlags();

	int GetMoveType();

	// You can't get the max health from netvars, and this is the only way to do it
	// GetMaxHealth is extremely useful on L4D1/L4D2 where the max hp isnt always 100
	int GetHealth();
	int GetMaxHealth();

	// Team functionality
	//Team* GetTeam();
	TeamType GetTeamNumber();
	bool IsInSameTeamAs(BaseEntity* other);
	bool IsInLocalTeam();
public:
	NETVAR(Vector3, Origin, DT_BaseEntity, m_vecOrigin);
	NETVAR(float, AnimTime, DT_BaseEntity, m_flAnimTime);
	NETVAR(float, Effects, DT_BaseEntity, m_fEffects);
	NETVAR(int, ModelIndex, DT_BaseEntity, m_nModelIndex);
	NETVAR(int, RenderMode, DT_BaseEntity, m_nRenderMode);
	NETVAR(int, RenderFX, DT_BaseEntity, m_nRenderFX);
	NETVAR(uintptr_t, Owner, DT_BaseEntity, m_hOwnerEntity);
};