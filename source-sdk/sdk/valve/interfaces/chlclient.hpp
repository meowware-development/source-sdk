#pragma once

#include "../structures/clientclass.hpp"
#include "../../utils/memory/memory.hpp"

class CHLClient
{
public:
	ClientClass* GetAllClasses()
	{
		return utils::memory::CallVirtualFunction<ClientClass*>(this, 8);
	}
};