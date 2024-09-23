#include "Player.h"

#include <cmath>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team)
	:
	Entity(Vector2D(x, y), "./Textures/Player.txt", team),
	projectile(Projectile(x, y, team, false)),
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

Projectile& Player::GetProjectile()
{
	return projectile;
}

void Player::Update()
{
	UpdateInputState();
	UpdateVelocity();
	UpdatePosition();
	projectile.Update();
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

	if (Engine::IsKeyDown(binds.projectileAttack))
	{
		if (!projectile.CheckFireState())
		{
			FireProjectile();
		}
	}
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
	if (direction != 0)
		velocity.x = Damp(velocity.x, targetSpeed * direction, walkAcceleration);
	else
		velocity.x = Damp(velocity.x, 0, stopAcceleration);

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
	/*if(GetPosition().x + GetImage().GetSize().X >= screenSize.X && velocity.x > 0)
	{
		SetPosition(screenSize.X - GetImage().GetSize().X, GetPosition().y);
		velocity.x = 0;
	}

	// Left screen bound
	if(GetPosition().x <= 0 && velocity.x < 0)
	{
		SetPosition(0, GetPosition().y);
		velocity.x = 0;
	}*/

	if(GetPosition().y + GetImage().GetSize().Y >= screenSize.Y && velocity.y > 0)
	{
		SetPosition(GetPosition().x, screenSize.Y - GetImage().GetSize().Y);
		velocity.y = 0;
		isOnGround = true;
	}
	else
		isOnGround = false;

	if(GetPosition().y <= 0 && velocity.y < 0)
	{
		SetPosition(GetPosition().x, 0);
		velocity.y = 0;
	}
}

void Player::UpdatePosition()
{
	Move(velocity * Engine::GetInstance().GetDeltaTime());
	ApplyBounds();
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
		playerToAttack->TakeDamage(attackDamage);
}

void Player::TakeDamage(const int damage)
{
	health -= damage;
}

void Player::FireProjectile()
{
	Vector2D projectileVelocity = Vector2D(lastDirection * projectileSpeed, 0);

	this->projectile.Fire(GetPosition(), projectileVelocity);
}
