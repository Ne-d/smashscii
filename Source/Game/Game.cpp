#include "Game.h"

Game::Game()
{
	AddTeam(0x0E);
	AddTeam(0x0F);

	AddPlayer(10, 10, { 'Q', 'D', VK_SPACE }, 0);
	AddPlayer(50, 10, { VK_LEFT, VK_RIGHT, VK_NUMPAD0 }, 1);
}

void Game::Update()
{
	for (Player* player : players)
		player->Update();
}

Player& Game::GetPlayer(const int number)
{
	return *players.at(number);
}

const std::vector<Player*>& Game::GetPlayers() const
{
	return players;
}

void Game::AddPlayer(const float x, const float y, const PlayerBinds binds, const unsigned int teamNb)
{
	players.push_back(new Player(x, y, binds, teams.at(teamNb)));
}

void Game::AddTeam(WORD attributes)
{
	teams.push_back(attributes);
}
