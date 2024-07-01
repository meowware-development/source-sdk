#pragma once
#include "cliententity.hpp"

#include "collideable.hpp"

#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"

#include "../datatypes/firebulletsinfo.hpp"
#include "../datatypes/takedamageinfo.hpp"
#include "../datatypes/studio.hpp"
#include "../datatypes/color.hpp"

#include "../enums/entity.hpp"

#include "../netvars/netvar.hpp"

struct Model;
class Team;

class BaseEntity : public ClientEntity {
public:
	static BaseEntity* GetLocalEntity();
	bool IsValid();
	int GetSolidFlags();
	int GetMoveType();

	// You can't get the max health from netvars, and this is the only way to do it
	// GetMaxHealth is extremely useful on L4D1/L4D2 where the max hp isnt always 100
	int GetHealth();
	int GetMaxHealth();

	// Team functionality
	Team* GetTeam();
	TeamID GetTeamNumber();
	bool IsInSameTeamAs(BaseEntity* other);
	bool IsInLocalTeam();

	bool IsPlayer();

	// Bone/Hitbox Position functionality
	Vector3 GetBonePosition(int bone);
	Vector3 GetBonePosition(Matrix3x4* boneMatrix, int bone);
	Vector3 GetHitboxPosition(int hitboxId);
	Vector3 GetHitboxPosition(Matrix3x4* boneMatrix, int hitboxId);
public:
	NETVAR(Vector3, Origin, DT_BaseEntity, m_vecOrigin);
	NETVAR(float, AnimTime, DT_BaseEntity, m_flAnimTime);
	NETVAR(float, Effects, DT_BaseEntity, m_fEffects);
	NETVAR(int, ModelIndex, DT_BaseEntity, m_nModelIndex);
	NETVAR(int, RenderMode, DT_BaseEntity, m_nRenderMode);
	NETVAR(int, RenderFX, DT_BaseEntity, m_nRenderFX);
	NETVAR(void*, Owner, DT_BaseEntity, m_hOwnerEntity);
};