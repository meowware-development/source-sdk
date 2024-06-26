#include "baseentity.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/debug/debug.hpp"
#include "../../indexes.hpp"

BaseEntity* BaseEntity::GetLocalEntity()
{
	return sdk::interfaces::entityList->GetClientEntity(sdk::interfaces::engine->GetLocalPlayer())->As<BaseEntity>();
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
	static auto offset = *reinterpret_cast<short*>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "80 B8 ?? ?? ?? ?? ?? A1") + 2);
	return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + offset);
}

int BaseEntity::GetHealth()
{
	return utils::memory::CallVirtualFunction<int>(this, sdk::indexes::C_BaseEntity::GetHealth);
}

int BaseEntity::GetMaxHealth()
{
	return utils::memory::CallVirtualFunction<int>(this, sdk::indexes::C_BaseEntity::GetMaxHealth);
}

Team* BaseEntity::GetTeam()
{
	return utils::memory::CallVirtualFunction<Team*>(this, 73);
}

int BaseEntity::GetTeamNumber()
{
	return utils::memory::CallVirtualFunction<int>(this, 74);
}

bool BaseEntity::IsInSameTeamAs(BaseEntity* other)
{
	return utils::memory::CallVirtualFunction<bool>(this, 77, other);
}

bool BaseEntity::IsInLocalTeam()
{
	return utils::memory::CallVirtualFunction<bool>(this, 78);
}
