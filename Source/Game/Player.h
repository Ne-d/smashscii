#pragma once

#include <windows.h>

#include "../Engine/Entity.h"

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
	void UpdateVelocity();
	void UpdatePosition();

private:
	PlayerBinds binds;

	const float targetSpeed = 60.f;
	const float walkAcceleration = 15.f;
	const float stopAcceleration = 20.f;
	Vector2D velocity;
	
	// Action states
	bool moveLeftState;
	bool moveRightState;

	WORD team;
};

