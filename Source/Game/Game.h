#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	Game();

	void Update();
	Player& GetPlayer(const int number);
	const std::vector<Player> GetPlayers() const;

	std::vector<Player> players;
};