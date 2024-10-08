#include "Game.h"
#include "../Engine/Engine.h"

Game::Game()
	:
	backgroundImage("./Textures/Background.txt", 0x0e),
	backgroundCollision("./Textures/Background.txt", 0x0),
	titleScreen("./Textures/Title.txt", 0x0e),
	endScreen("./Textures/End.txt", 0x0e)
{
	AddPlayer(10, 10, { 'Q', 'D', VK_SPACE, VK_CONTROL },
		FOREGROUND_BLUE + FOREGROUND_GREEN, 0);
	AddPlayer(50, 10, { VK_LEFT, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1 },
		FOREGROUND_RED + FOREGROUND_INTENSITY, 1);
}

/**
 * Method called every frame to update all players, and the HUD.
 */
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

const Image* Game::GetTitleImage() const
{
	return &titleScreen;
}

/**
 * Adds a new player to the game.
 * @param x The starting x coordinate of the player.
 * @param y The starting y coordinate of the player.
 * @param binds The key bindings of the new player.
 * @param team The team of the new player.
 * @param playerNumber The player number.
 */
void Game::AddPlayer(const float x, const float y, const PlayerBinds binds, const WORD team, const int playerNumber)
{
	players.push_back(new Player(x, y, binds, team, playerNumber));
}

/**
 * Draws a HUD containing the players' health values.
 */
void Game::DrawPlayerHealth() const
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		std::wstring const text = L" Player " + std::to_wstring(i + 1) + L" health: "
								  + std::to_wstring(players.at(i)->GetHealth()) + L" ";
		
		const short xCoord = 1 + static_cast<short>(i) * 96;
		Engine::GetInstance()->WriteText(text, COORD{xCoord, 0}, players.at(i)->GetTeam());
	}
}

void Game::DrawBackground() const
{
	Engine::GetInstance()->DrawImage(backgroundImage, COORD{0, 0});
}

void Game::DrawTitle() const
{
	Engine::GetInstance()->DrawImage(titleScreen, COORD{0, 0});
}

void Game::DrawEnd() const
{
	Engine::GetInstance()->DrawImage(endScreen, COORD{0, 0});
}
