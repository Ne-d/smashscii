#pragma once

#include <vector>

#include "Player.h"
#include "../Engine/Background.h"

class Game
{
public:
	Game();

	void Update() const;

	Player& GetPlayer(unsigned int number) const;
	const std::vector<Player*>& GetPlayers() const;
	const Image* GetBackgroundCollision() const;

	void AddPlayer(float x, float y, PlayerBinds binds, WORD team);
	void AddTeam(WORD attributes);

	void DrawPlayerHealth() const;
	void DrawBackground();

private:
	std::vector<Player*> players;
	std::vector<WORD> teams;

	Image backgroundImage;
	Image backgroundCollision;
};
