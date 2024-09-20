#pragma once
#include "../Engine/Entity.h"
#include <Windows.h>

struct PlayerBinds
{
	WORD moveLeftBind;
	WORD moveRightBind;
};

class Player : public Entity
{
public:
	explicit Player(float x = 0, float y = 0, PlayerBinds binds = {'Q', 'D'}, WORD team = 0);

	void SetBinds(PlayerBinds newBinds);
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

