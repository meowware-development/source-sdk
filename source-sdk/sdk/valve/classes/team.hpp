#pragma once

class Team {
public:
	char* GetName(void);
	int	GetScore(void);

	bool ContainsPlayer(int playerIndex);

	int	GetNumberOfPlayers(void);
};