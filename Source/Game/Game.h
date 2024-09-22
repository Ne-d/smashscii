#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	Game();

	void Update();

	Player& GetPlayer(int number);
	const std::vector<Player*>& GetPlayers() const;

	void AddPlayer(float x, float y, PlayerBinds binds, unsigned int teamNb);
	void AddTeam(WORD attributes);

	void DrawPlayerHealth() const;

private:
	std::vector<Player*> players;
	std::vector<WORD> teams;
};