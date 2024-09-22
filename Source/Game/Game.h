#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	Game();

	void Update() const;

	Player& GetPlayer(unsigned int number) const;
	const std::vector<Player*>& GetPlayers() const;

	void AddPlayer(float x, float y, PlayerBinds binds, unsigned int teamNb);
	void AddTeam(WORD attributes);

	void DrawPlayerHealth() const;

private:
	std::vector<Player*> players;
	std::vector<WORD> teams;
};