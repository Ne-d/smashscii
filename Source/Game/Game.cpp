#include "Game.h"
#include "../Engine/Engine.h"

Game::Game()
	:
	backgroundImage("./Textures/Background.txt", 0x0e),
	backgroundCollision("./Textures/Background.txt", 0x0)
{
	AddTeam(0x0E);
	AddTeam(0x0F);

	AddPlayer(10, 10, { 'Q', 'D', VK_SPACE, VK_CONTROL },
		FOREGROUND_BLUE + FOREGROUND_GREEN);
	AddPlayer(50, 10, { VK_LEFT, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1 },
		FOREGROUND_RED + FOREGROUND_INTENSITY);
}

void Game::Update() const
{
	for (Player* player : players)
		player->Update();

	DrawPlayerHealth();
}

Player& Game::GetPlayer(const unsigned int number) const
{
	return *players.at(number);
}

const std::vector<Player*>& Game::GetPlayers() const
{
	return players;
}

const Image* Game::GetBackgroundCollision() const
{
	return &backgroundImage;
}

void Game::AddPlayer(const float x, const float y, const PlayerBinds binds, const WORD team)
{
	players.push_back(new Player(x, y, binds, team));
}

void Game::AddTeam(const WORD attributes)
{
	teams.push_back(attributes);
}

void Game::DrawPlayerHealth() const
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		std::wstring const text = L" Player " + std::to_wstring(i) + L" health: "
								  + std::to_wstring(players.at(i)->GetHealth()) + L" ";
		
		const short xCoord = 1 + static_cast<short>(i) * 96;
		Engine::GetInstance().WriteText(text, COORD{xCoord, 0}, players.at(i)->GetTeam());
	}
}

void Game::DrawBackground()
{
	Engine::GetInstance().DrawImage(backgroundImage, COORD{0, 0});
}
