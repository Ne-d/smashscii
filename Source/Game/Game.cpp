#include "Game.h"

Game::Game()
	:
	players(std::vector<Player>(2))
{
	players.emplace_back();
	players.at(0).SetPosition(10, 10);
	PlayerBinds player1Binds;
	player1Binds.moveLeftBind = 'Q';
	player1Binds.moveRightBind = 'D';
	players.at(0).SetBinds(player1Binds);

	players.emplace_back();
	PlayerBinds player2Binds;
	player2Binds.moveLeftBind = VK_LEFT;
	player2Binds.moveRightBind = VK_RIGHT;
	players.at(1).SetBinds(player2Binds);
	players.at(1).SetPosition(20, 10);
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
