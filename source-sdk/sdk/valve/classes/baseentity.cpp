#include "baseentity.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/debug/debug.hpp"
#include "../../signatures.hpp"
#include "../../math/math.hpp"

BaseEntity* BaseEntity::GetLocalEntity()
{
	return sdk::interfaces::entityList->GetClientEntity(sdk::interfaces::engine->GetLocalPlayer())->As<BaseEntity>();
}

bool BaseEntity::IsValid()
{
	return this != nullptr;
}

int BaseEntity::GetSolidFlags()
{
	auto collideable = GetCollideable();
	if (!collideable)
		return -1;

	return collideable->GetSolidFlags();
}

int BaseEntity::GetMoveType()
{
	static auto offset = *utils::memory::PatternScan(utils::memory::GetModule("client.dll"), sdk::signatures::client::C_BaseEntity::MoveType::sig).Cast<short*>(sdk::signatures::client::C_BaseEntity::MoveType::offset);
	return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + offset);
}

int BaseEntity::GetHealth()
{
	return utils::memory::CallVirtualFunction<int>(this, 106);
}

int BaseEntity::GetMaxHealth()
{
	return utils::memory::CallVirtualFunction<int>(this, 107);
}

Team* BaseEntity::GetTeam()
{
	return utils::memory::CallVirtualFunction<Team*>(this, 73);
}

TeamID BaseEntity::GetTeamNumber()
{
	return utils::memory::CallVirtualFunction<TeamID>(this, 74);
}

bool BaseEntity::IsInSameTeamAs(BaseEntity* other)
{
	return utils::memory::CallVirtualFunction<bool>(this, 77, other);
}

bool BaseEntity::IsInLocalTeam()
{
	return utils::memory::CallVirtualFunction<bool>(this, 78);
}

bool BaseEntity::IsPlayer()
{
	return utils::memory::CallVirtualFunction<bool>(this, 131);
}

Vector3 BaseEntity::GetBonePosition(int bone) {
	Matrix3x4 boneMatrix[MAXSTUDIOBONES];
	if (this->SetupBones(boneMatrix, MAXSTUDIOBONES, 256, 0.0f))
		return Vector3(boneMatrix[bone][0][3], boneMatrix[bone][1][3], boneMatrix[bone][2][3]);

	return Vector3();
}

// In case you care about performance, you should call SetupBones only once, and then pass into as many calls as you want.
// You SHOULD use this while searching for the ideal bone for the aimbot to shoot at.
Vector3 BaseEntity::GetBonePosition(Matrix3x4* boneMatrix, int bone) {
	return Vector3(boneMatrix[bone][0][3], boneMatrix[bone][1][3], boneMatrix[bone][2][3]);
}

Vector3 BaseEntity::GetHitboxPosition(int hitboxId) {
	Matrix3x4 boneMatrix[MAXSTUDIOBONES];

	if (!this->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f))
		return Vector3();

	StudioHDR* studioModel = sdk::interfaces::modelInfo->GetStudioModel(this->GetModel());

	if (!studioModel)
		return Vector3();

	auto hitboxSet = studioModel->HitboxSet(0);

	if (!hitboxSet)
		return Vector3();

	auto hitbox = hitboxSet->Hitbox(hitboxId);

	if (!hitbox)
		return Vector3();

	Vector3 min, max;

	sdk::math::TransformVector(hitbox->mins, boneMatrix[hitbox->bone], min);
	sdk::math::TransformVector(hitbox->maxs, boneMatrix[hitbox->bone], max);

	return (min + max) * 0.5f;
}

// In case you care about performance, you should call SetupBones only once, and then pass into as many calls as you want.
// You SHOULD use this while searching for the ideal hitbox for the aimbot to shoot at.
Vector3 BaseEntity::GetHitboxPosition(Matrix3x4* boneMatrix, int hitboxId) {
	StudioHDR* studioModel = sdk::interfaces::modelInfo->GetStudioModel(this->GetModel());

	if (!studioModel)
		return Vector3();

	auto hitboxSet = studioModel->HitboxSet(0);

	if (!hitboxSet)
		return Vector3();

	auto hitbox = hitboxSet->Hitbox(hitboxId);

	if (!hitbox)
		return Vector3();

	Vector3 min, max;

	sdk::math::TransformVector(hitbox->mins, boneMatrix[hitbox->bone], min);
	sdk::math::TransformVector(hitbox->maxs, boneMatrix[hitbox->bone], max);

	return (min + max) * 0.5f;
}