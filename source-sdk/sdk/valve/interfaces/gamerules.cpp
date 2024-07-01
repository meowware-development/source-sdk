#include "gamerules.hpp"
#include "../../../utils/memory/memory.hpp"

ViewVectors* GameRules::GetViewVectors()
{
	return utils::memory::CallVirtualFunction<ViewVectors*>(this, 31);
}