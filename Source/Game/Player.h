#pragma once

#include <windows.h>

#include "../Engine/Entity.h"
#include "Projectile.h"

struct PlayerBinds
{
	WORD moveLeftBind;
	WORD moveRightBind;
	WORD projectileAttack;
};

class Player : public Entity
{
public:
	explicit Player(float x = 0, float y = 0, PlayerBinds binds = {'Q', 'D', 'F'}, WORD team = 0);

	void SetBinds(PlayerBinds newBinds);
	void SetTeam(WORD team);
	
	void Update();
	void UpdateInputState();
	void UpdateVelocity();
	void ApplyBounds();
	void UpdatePosition();

private:
	void FireProjectile();

	PlayerBinds binds;

	Projectile projectile;

	const float targetSpeed = 60.f;
	const float walkAcceleration = 15.f;
	const float stopAcceleration = 20.f;

	const float gravitySpeed = 60.f;
	const float gravityAcceleration = 5.f;

	const float projectileSpeed = 1.f;
	
	Vector2D velocity;

	bool isOnGround = false;
	bool isAimingRight = false;
	
	// Action states
	bool moveLeftState;
	bool moveRightState;

	WORD team;
};

