#include "baseentity.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/debug/debug.hpp"

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
