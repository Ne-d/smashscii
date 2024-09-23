#include "Game.h"
#include "../Engine/Engine.h"

Game::Game()
{
	AddTeam(0x0E);
	AddTeam(0x0F);

	AddPlayer(10, 10, { 'Q', 'D', VK_SPACE, VK_CONTROL, VK_SHIFT }, 0);
	AddPlayer(50, 10, { VK_LEFT, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2 }, 1);
}

void Game::Update()
{
	for (Player* player : players)
		player->Update();

	DrawPlayerHealth();
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

void Game::DrawPlayerHealth() const
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		std::wstring const text = L"Player " + std::to_wstring(i) + L" health: "
								  + std::to_wstring(players.at(i)->GetHealth());
		
		short const xCoord = static_cast<short>(i) * 50;
		Engine::GetInstance().WriteText(text, COORD{xCoord, 0}, players.at(i)->GetTeam());
	}
}
