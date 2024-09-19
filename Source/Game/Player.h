#pragma once
#include "../Engine/Entity.h"
#include <map>
#include <Windows.h>
#include <vector>
#include <functional>

struct PlayerBinds
{
	WORD moveLeftBind;
	WORD moveRightBind;
};

class Player : public Entity
{
public:
	Player(unsigned int x = 0, unsigned int y = 0, PlayerBinds binds = {'Q', 'D'}, WORD team = 0);

	void SetBinds(const PlayerBinds newBinds);
	void SetTeam(WORD team);
	
	void Update();
	void UpdateInputState();
	void UpdatePosition();

private:
	PlayerBinds binds;

	// Action states
	bool moveLeftState;
	bool moveRightState;

	WORD team;
};

