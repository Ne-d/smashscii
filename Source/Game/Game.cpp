#include "Game.h"

Game::Game()
{
	AddTeam(0x0E);
	AddTeam(0x0F);

	AddPlayer(10, 10, { 'Q', 'D' }, 0);
	AddPlayer(50, 10, { VK_LEFT, VK_RIGHT }, 1);
}

void Game::Update()
{
	for (Player& player : players)
		player.Update();
}

Player& Game::GetPlayer(const int number)
{
	return players.at(number);
}

const std::vector<Player> Game::GetPlayers() const
{
	return players;
}

void Game::AddPlayer(int x, int y, PlayerBinds binds, unsigned int teamNb)
{
	players.emplace_back(x, y, binds, teamNb);
}

void Game::AddTeam(WORD attributes)
{
	teams.push_back(attributes);
}
