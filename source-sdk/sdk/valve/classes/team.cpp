#include "team.hpp"
#include "../../../utils/memory/memory.hpp"

char* Team::GetName(void)
{
	return utils::memory::CallVirtualFunction<char*>(this, 158);
}

int Team::GetScore(void)
{
	//return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x54C);
	return utils::memory::CallVirtualFunction<int>(this, 159);
}

bool Team::ContainsPlayer(int playerIndex)
{
	return utils::memory::CallVirtualFunction<bool>(this, 163, playerIndex);
}

int Team::GetNumberOfPlayers(void)
{
	return utils::memory::CallVirtualFunction<int>(this, 164);
}
