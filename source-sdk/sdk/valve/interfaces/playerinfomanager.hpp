#pragma once

#include "../datatypes/globalvars.hpp"

class PlayerInfoManager
{
public:
	virtual void* GetPlayerInfo(void* pEdict) = 0;
	virtual GlobalVars* GetGlobalVars() = 0;
};