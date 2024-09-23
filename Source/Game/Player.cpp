#include "Player.h"

#include <cmath>
#include <iostream>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team)
	:
	Entity(Vector2D(x, y), "./Textures/Player.txt", team),
	binds(binds),
	moveLeftState(false),
	moveRightState(false),
	direction(0),
	lastDirection(1),
	jumpState(false),
	attackState(false),
	team(team)
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

void Player::Update()
{
	UpdateInputState();
	UpdateVelocity();
	UpdatePosition();

	if(health <= 0)
		exit(0); // TODO: Not thread-safe
}

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

	if(!attackState && Engine::IsKeyDown(binds.attack))
	{
		attackState = true;
		TryAttack();
	}
	if(!Engine::IsKeyDown(binds.attack))
		attackState = false;
}

// Shamelessly stolen from https://www.febucci.com/2018/08/easing-functions/.
float Lerp(const float startValue, const float endValue, const float factor)
{
	return startValue + (endValue - startValue) * factor;
}

// Adapted from from https://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/.
float Damp(const float startValue, const float endValue, const float lambda)
{
	return Lerp(startValue, endValue, 1 - std::exp(-lambda * Engine::GetInstance().GetDeltaTime()));
}

void Player::UpdateVelocity()
{
	// Horizontal movement
	if (direction != 0)
		velocity.x = Damp(velocity.x, targetSpeed * static_cast<float>(direction), walkAcceleration);
	else
		if(isOnGround)
			velocity.x = Damp(velocity.x, 0, stopAccelerationGround);
		else
			velocity.x = Damp(velocity.x, 0, stopAccelerationAir);

	// Gravity
	if(!isOnGround)
		velocity.y = Damp(velocity.y, gravitySpeed, gravityAcceleration);

	if (jumpState && isOnGround)
	{
		velocity.y = jumpVelocity;
	}
}

void Player::ApplyBounds()
{
	const COORD screenSize = Engine::GetInstance().GetScreenSize();

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

void Player::ApplyCollisions()
{
	const Image* collision = Engine::GetInstance().GetGame().GetBackgroundCollision();

	// Store every point to test collision on.
	std::vector<COORD> collisionPoints;
	collisionPoints.reserve(3);
	for(int i = 0; i < GetImage().GetSize().X; ++i)
	{
		const short x = static_cast<short>(GetPosition().x) + static_cast<short>(i);
		const short y = static_cast<short>(GetPosition().y) + GetImage().GetSize().Y;
		
		collisionPoints.push_back(COORD{x, y});
	}

	for(const COORD& collisionPoint : collisionPoints)
	{
		if(collision->GetChar(collisionPoint.X, collisionPoint.Y).Char.UnicodeChar != ' ' && velocity.y >= 0)
		{
			velocity.y = 0;
			isOnGround = true;
		}
	}
}

void Player::UpdatePosition()
{
	Move(velocity * Engine::GetInstance().GetDeltaTime());
	ApplyBounds();
	ApplyCollisions();
}

void Player::TryAttack() const
{
	std::vector<Player*> const players = Engine::GetInstance().GetGame().GetPlayers();

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
		// If we are moving left, check if the player is to our left, adn within range.
		else if(lastDirection == -1)
		{
			if(player->GetPosition().x < GetPosition().x && player->GetPosition().x > GetPosition().x - horizontalAttackRange)
			{
				playerToAttack = player;
				break;
			}
		}
	}
	
	if (playerToAttack != nullptr
		&& playerToAttack->GetPosition().y >= GetPosition().y - verticalAttackRange
		&& playerToAttack->GetPosition().y <= GetPosition().y + verticalAttackRange)
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
