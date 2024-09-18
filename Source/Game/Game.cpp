#include "Game.h"

Game::Game()
	:
	players(std::vector<Player>(2))
{
}

Player& Game::getPlayer(const int number)
{
	return players.at(number);
}
