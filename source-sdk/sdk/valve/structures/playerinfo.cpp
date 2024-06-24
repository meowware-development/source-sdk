#include "playerinfo.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../interfaces/interfaces.hpp"

PlayerInfo PlayerInfo::Get(int idx)
{
	PlayerInfo info{};

	if (!sdk::interfaces::engine)
		return info;

	sdk::interfaces::engine->GetPlayerInfo(idx, &info);
	return info;
}
