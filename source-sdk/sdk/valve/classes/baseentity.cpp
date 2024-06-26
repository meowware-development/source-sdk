#include "baseentity.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/debug/debug.hpp"
#include "../../signatures.hpp"

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
	static auto offset = *reinterpret_cast<short*>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), sdk::signatures::client::C_BaseEntity::MoveType::sig) + sdk::signatures::client::C_BaseEntity::MoveType::offset);
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
