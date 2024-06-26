#pragma once
#include "../classes/baseentity.hpp"
#include "memutil.hpp"

struct Team : public BaseEntity {
	// Data Handling
	virtual char* GetName(void);
	virtual int		GetScore(void);

	virtual bool	ContainsPlayer(int playerIndex);

	// for shared code, use the same function name
	virtual int		GetNumberOfPlayers(void);
};