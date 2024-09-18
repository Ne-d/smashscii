#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	Game();

	void Update();
	Player& getPlayer(const int number);

	std::vector<Player> players;
};