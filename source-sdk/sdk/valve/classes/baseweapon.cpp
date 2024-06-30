#include "baseweapon.hpp"
#include "../../../utils/memory/memory.hpp"

const char* BaseWeapon::GetName()
{
	return utils::memory::CallVirtualFunction<const char*>(this, 311);
}
