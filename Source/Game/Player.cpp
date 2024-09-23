#include "Player.h"

#include <cmath>
#include <iostream>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team, const int playerNumber)
	:
	Entity(Vector2D(x, y), "./Textures/Player.txt", team),
	playerNumber(playerNumber),
	team(team),
	binds(binds),
	moveLeftState(false),
	moveRightState(false),
	direction(0),
	lastDirection(1),
	jumpState(false),
	attackState(false)
{
	SetPosition(x, y);
}

void Player::SetBinds(const PlayerBinds newBinds)
{
	this->binds = newBinds;
}

void Player::SetTeam(const WORD team)
{
	this->team = team;
}

int Player::GetHealth() const
{
	return health;
}

WORD Player::GetTeam() const
{
	return team;
}

/**
 * Method called each frame to handle player movement and keep track of death.
 */
void Player::Update()
{
	UpdateInputState();
	UpdateVelocity();
	UpdatePosition();

	if(health <= 0)
		// HACK: This only works for two players.
		EndGame((playerNumber + 1) % 2);
		
}

/**
 * Checks inputs to update the player's input state variables.
 */
void Player::UpdateInputState()
{
	moveLeftState = Engine::IsKeyDown(binds.moveLeft);
	moveRightState = Engine::IsKeyDown(binds.moveRight);

	// 1 if we are moving right, -1 if we are moving left, and 0 if we are not moving, or pressing both directions at once.
	direction = static_cast<int>(moveRightState) - static_cast<int>(moveLeftState);

	// Used to keep a direction to attack, even when not moving.
	if(direction != 0)
		lastDirection = direction;

	jumpState = Engine::IsKeyDown(binds.jump);

	// Attacks happen only on the first frame that the key is pressed.
	if(!attackState && Engine::IsKeyDown(binds.attack))
	{
		attackState = true;
		TryAttack();
	}
	if(!Engine::IsKeyDown(binds.attack))
		attackState = false;
}

// Shamelessly stolen from https://www.febucci.com/2018/08/easing-functions/
// Linear interploation between startValue and endValue, with the given factor.
float Lerp(const float startValue, const float endValue, const float factor)
{
	return startValue + (endValue - startValue) * factor;
}

// Adapted from  https://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/.
// Framerate-independent version of Lerp.
float Damp(const float startValue, const float endValue, const float lambda)
{
	return Lerp(startValue, endValue, 1 - std::exp(-lambda * Engine::GetInstance()->GetDeltaTime()));
}

/**
 * Calculates the player's new velocity based on the input state.
 */
void Player::UpdateVelocity()
{
	// Horizontal movement
	if (direction != 0)
		velocity.x = Damp(velocity.x, targetSpeed * static_cast<float>(direction), walkAcceleration);
	else
		// Stopping faster on the ground than in the air.
		if(isOnGround)
			velocity.x = Damp(velocity.x, 0, stopAccelerationGround);
		else
			velocity.x = Damp(velocity.x, 0, stopAccelerationAir);

	// Gravity
	if(!isOnGround)
		velocity.y = Damp(velocity.y, gravitySpeed, gravityAcceleration);

	// Jumping
	if (jumpState && isOnGround)
		velocity.y = jumpVelocity;
}

/**
 * Enforces boundaries on the edges of the screen, to prevent the player from going off-screen.
 */
void Player::ApplyBounds()
{
	const COORD screenSize = Engine::GetInstance()->GetScreenSize();

	// Right screen bound
	if(GetPosition().x + static_cast<float>(GetImage().GetSize().X) >= static_cast<float>(screenSize.X) - 1 && velocity.x > 0)
	{
		SetPosition(static_cast<float>(screenSize.X) - static_cast<float>(GetImage().GetSize().X) - 1, GetPosition().y);
		velocity.x = 0;
	}

	// Left screen bound
	if(GetPosition().x <= 1 && velocity.x < 0)
	{
		SetPosition(1, GetPosition().y);
		velocity.x = 0;
	}

	// Lower screen bound
	if(GetPosition().y + static_cast<float>(GetImage().GetSize().Y) >= static_cast<float>(screenSize.Y) - 1 && velocity.y > 0)
	{
		SetPosition(GetPosition().x, static_cast<float>(screenSize.Y) - static_cast<float>(GetImage().GetSize().Y) - 1);
		velocity.y = 0;
		isOnGround = true;
	}
	else
		isOnGround = false;

	// Upper screen bound
	if(GetPosition().y <= 1 && velocity.y < 0)
	{
		SetPosition(GetPosition().x, 1);
		velocity.y = 0;
	}
}

/**
 * Enforces collisions with the collision "tile map".
 */
void Player::ApplyCollisions()
{
	const Image* collision = Engine::GetInstance()->GetGame().GetBackgroundCollision();

	// Store every point to test collision on.
	std::vector<COORD> collisionPoints;
	collisionPoints.reserve(3); // To save on exactly 2 calls to new ;)

	// Add every point at the base of the player to the list of collision points.
	for(int i = 0; i < GetImage().GetSize().X; ++i)
	{
		const short x = static_cast<short>(GetPosition().x) + static_cast<short>(i);
		const short y = static_cast<short>(GetPosition().y) + GetImage().GetSize().Y;
		
		collisionPoints.push_back(COORD{x, y});
	}

	// Check collisions with every collision point.
	for(const COORD& collisionPoint : collisionPoints)
	{
		// HACK: Accessing a member of a union is technically unsafe.
		// We only ever write to UnicodeChar so it has no reason to fail, though.
		if(collision->GetChar(collisionPoint.X, collisionPoint.Y).Char.UnicodeChar != ' ' && velocity.y >= 0)
		{
			velocity.y = 0;
			isOnGround = true;
		}
	}
}

/**
 * Updates the position based on the velocity.
 */
void Player::UpdatePosition()
{
	Move(velocity * Engine::GetInstance()->GetDeltaTime());
	ApplyBounds();
	ApplyCollisions();
}

/**
 * Ends the game.
 * @param winner The number of the player who won the game.
 */
void Player::EndGame(const int winner)
{
	Engine::GetInstance()->EndGame(winner);
}

/**
 * Check if it is possible to attack a player.
 */
void Player::TryAttack() const
{
	std::vector<Player*> const players = Engine::GetInstance()->GetGame().GetPlayers();

	Player* playerToAttack = nullptr;
	
	for (Player* const player : players)
	{
		// If we are moving right, check if the player is to our right, and within range.
		if(lastDirection == 1)
		{
			if(player->GetPosition().x > GetPosition().x && player->GetPosition().x < GetPosition().x + horizontalAttackRange)
			{
				playerToAttack = player;
				break;
			}
		}
		// If we are moving left, check if the player is to our left, and within range.
		else if(lastDirection == -1)
		{
			if(player->GetPosition().x < GetPosition().x && player->GetPosition().x > GetPosition().x - horizontalAttackRange)
			{
				playerToAttack = player;
				break;
			}
		}
	}

	// If a player has been found, is within vertical range, and has a different team than ourselves, attack.
	if (playerToAttack != nullptr
		&& playerToAttack->GetPosition().y >= GetPosition().y - verticalAttackRange
		&& playerToAttack->GetPosition().y <= GetPosition().y + verticalAttackRange
		&& playerToAttack->GetTeam() != GetTeam())
	{
		playerToAttack->TakeDamage(attackDamage, Vector2D(static_cast<float>(lastDirection) * horizontalKnockback,
			verticalKnockback));
	}
}

void Player::TakeDamage(const int damage, const Vector2D& knockback)
{
	health -= damage;
	velocity += knockback;
}
