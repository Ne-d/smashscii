#pragma once

#include <vector>

#include "Player.h"

class Game
{
public:
	// Constructor
	Game();

	// Accessors
	Player& GetPlayer(unsigned int number) const;
	const std::vector<Player*>& GetPlayers() const;
	const Image* GetBackgroundCollision() const;
	const Image* GetTitleImage() const;

	void AddPlayer(float x, float y, PlayerBinds binds, WORD team, int playerNumber);

	// Gameplay methods
	void Update() const;
	void DrawPlayerHealth() const;
	void DrawBackground() const;
	void DrawTitle() const;
	void DrawEnd() const;

private: // Data
	std::vector<Player*> players;

	// Images
	Image backgroundImage;
	Image backgroundCollision;
	Image titleScreen;
	Image endScreen;
};
