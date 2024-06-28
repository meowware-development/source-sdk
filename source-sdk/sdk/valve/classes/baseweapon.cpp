#include "baseweapon.hpp"
#include "../../../utils/memory/memory.hpp"

const char* BaseWeaapon::GetName()
{
    return utils::memory::CallVirtualFunction<const char*>(this, 311);
}
