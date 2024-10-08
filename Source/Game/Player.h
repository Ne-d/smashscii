#pragma once

#include <windows.h>

#include "../Engine/Entity.h"

// Stores the key bindings for each action a player can perform.
// The values are keycodes compatible with Windows' API
struct PlayerBinds
{
	WORD moveLeft;
	WORD moveRight;
	WORD jump;
	WORD attack;
};

class Player : public Entity
{
public:
	// Constructors
	explicit Player(float x = 0, float y = 0, PlayerBinds binds = {'Q', 'D', VK_SPACE, VK_CONTROL}, WORD team = 0, int playerNumber = 0);

	// Accessors
	void SetBinds(PlayerBinds newBinds);
	void SetTeam(WORD team);

	int GetHealth() const;
	WORD GetTeam() const;

	// Gameplay methods
	void Update();
	void UpdateInputState();
	void UpdateVelocity();
	void ApplyBounds();
	void ApplyCollisions();
	void UpdatePosition();
	static void EndGame(int winner);

	void TryAttack() const;
	void TakeDamage(int damage, const Vector2D& knockback);

private: // Data
	int playerNumber;
	WORD team;
	PlayerBinds binds;

	// Gameplay constants
	const float targetSpeed = 60.f;
	const float walkAcceleration = 15.f;
	const float stopAccelerationGround = 20.f;
	const float stopAccelerationAir = 5.f;

	const float gravitySpeed = 50.f;
	const float gravityAcceleration = 4.f;
	const float jumpVelocity = -100.f;

	const float horizontalAttackRange = 10.f;
	const float verticalAttackRange = 5.f;
	const float horizontalKnockback = 100;
	const float verticalKnockback = -30;

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
};

