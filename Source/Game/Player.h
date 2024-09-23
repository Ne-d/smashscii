#pragma once

#include <windows.h>

#include "../Engine/Entity.h"
#include "Projectile.h"

struct PlayerBinds
{
	WORD moveLeft;
	WORD moveRight;
	WORD jump;
	WORD attack;
	WORD projectileAttack;
};

class Player : public Entity
{
public:
	explicit Player(float x = 0, float y = 0, PlayerBinds binds = {'Q', 'D', VK_SPACE, VK_CONTROL, VK_SHIFT}, WORD team = 0);

	void SetBinds(PlayerBinds newBinds);
	void SetTeam(WORD team);

	int GetHealth() const;
	WORD GetTeam() const;
	Projectile& GetProjectile();
	
	void Update();
	void UpdateInputState();
	void UpdateVelocity();
	void ApplyBounds();
	void UpdatePosition();
	
	void TryAttack() const;
	void TakeDamage(int damage);

private:
	void FireProjectile();

	PlayerBinds binds;
	
	Projectile projectile;

	// Movement constants
	const float targetSpeed = 60.f;
	const float walkAcceleration = 15.f;
	const float stopAcceleration = 20.f;
	
	const float gravitySpeed = 50.f;
	const float gravityAcceleration = 4.f;

	const float jumpVelocity = -100.f;

	const float horizontalAttackRange = 10.f;
	const float verticalAttackRange = 5.f;

	const float projectileSpeed = .1f;

	// Movement variables
	Vector2D velocity;
	bool isOnGround = false;

	int health = 100;
	const int attackDamage = 5;
	
	// Action states
	bool moveLeftState;
	bool moveRightState;
	int direction;
	int lastDirection;
	
	bool jumpState;
	bool attackState;

	WORD team;
};

