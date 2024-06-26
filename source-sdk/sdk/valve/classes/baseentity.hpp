#pragma once
#include "cliententity.hpp"

#include "../../math/vector.hpp"

#include "../structures/firebulletsinfo.hpp"
#include "../structures/takedamageinfo.hpp"
#include "../structures/studio.hpp"
#include "collideable.hpp"

#include "../misc/color.hpp"

#include "../netvars/netvar.hpp"

struct Model;
struct Team;

class BaseEntity : public ClientEntity {
public:
	static BaseEntity* GetLocalEntity();
	int GetSolidFlags();

	int GetMoveType();

	// You can't get the max health from netvars, and this is the only way to do it
	// GetMaxHealth is extremely useful on L4D1/L4D2 where the max hp isnt always 100
	int GetHealth();
	int GetMaxHealth();
public:
	NETVAR(Vector3, Origin, DT_BaseEntity, m_vecOrigin);
	NETVAR(float, AnimTime, DT_BaseEntity, m_flAnimTime);
	NETVAR(float, Effects, DT_BaseEntity, m_fEffects);
	NETVAR(int, ModelIndex, DT_BaseEntity, m_nModelIndex);
	NETVAR(int, RenderMode, DT_BaseEntity, m_nRenderMode);
	NETVAR(int, RenderFX, DT_BaseEntity, m_nRenderFX);
	NETVAR(int, Team, DT_BaseEntity, m_iTeamNum);
	NETVAR(uintptr_t, Owner, DT_BaseEntity, m_hOwnerEntity);
};