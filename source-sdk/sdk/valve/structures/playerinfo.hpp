#pragma once
#include <cstdint>

struct PlayerInfo
{
	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[33];
	// friends identification number
	uint32_t			friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned int			customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;

	static PlayerInfo Get(int idx);
};