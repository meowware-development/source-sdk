#pragma once
#include "../classes/baseentity.hpp"
#include "memutil.hpp"

struct Team : public BaseEntity {
	virtual			~Team() = 0;

	virtual void	PreDataUpdate(DataUpdateType updateType) = 0;

	// Data Handling
	virtual char* Get_Name(void) = 0;
	virtual int		Get_Score(void) = 0;
	virtual int		Get_Deaths(void) = 0;
	virtual int		Get_Ping(void) = 0;

	// Player Handling
	virtual int		GetNumberOfPlayers(void) = 0;
	virtual bool	ContainsPlayer(int iPlayerIndex) = 0;

	// for shared code, use the same function name
	virtual int		GetNumPlayers(void) = 0;

	CUtlVector< int > m_aPlayers;
	char	m_szTeamname[32];
	int		m_iScore;
	int		m_iRoundsWon;

	// Data for the scoreboard
	int		m_iDeaths;
	int		m_iPing;
	int		m_iPacketloss;
	int		m_iTeamNum;
};