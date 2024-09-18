#include "Game.h"

Game::Game()
	:
	players(std::vector<Player>(2))
{
	players.emplace_back();
	players.at(1).SetPosition(10, 50);

	players.emplace_back();
	players.at(2).SetPosition(100, 50);
}

void Game::Update()
{
	for (Player& player : players)
		player.Update();
}

Player& Game::getPlayer(const int number)
{
	return players.at(number);
}
