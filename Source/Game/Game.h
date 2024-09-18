#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	Game();

	std::vector<Player> players;

	Player& getPlayer(const int number);
};