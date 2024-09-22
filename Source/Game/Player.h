#pragma once

#include <windows.h>

#include "../Engine/Entity.h"

struct PlayerBinds
{
	WORD moveLeft;
	WORD moveRight;
	WORD jump;
};

class Player : public Entity
{
public:
	explicit Player(float x = 0, float y = 0, PlayerBinds binds = {'Q', 'D', VK_SPACE}, WORD team = 0);

	void SetBinds(PlayerBinds newBinds);
	void SetTeam(WORD team);
	
	void Update();
	void UpdateInputState();
	void UpdateVelocity();
	void ApplyBounds();
	void UpdatePosition();

private:
	PlayerBinds binds;

	const float targetSpeed = 60.f;
	const float walkAcceleration = 15.f;
	const float stopAcceleration = 20.f;

	const float gravitySpeed = 50.f;
	const float gravityAcceleration = 4.f;

	const float jumpVelocity = -100.f;
	
	Vector2D velocity;

	bool isOnGround = false;
	
	// Action states
	bool moveLeftState;
	bool moveRightState;

	WORD team;
	bool jumpState;
};

