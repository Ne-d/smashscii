#include "Player.h"

#include <cmath>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team)
	:
	Entity(Vector2D(x, y), "./Textures/Player.txt", team),
	binds(binds),
	moveLeftState(false),
	moveRightState(false),
	team(team)
{
	SetPosition(x, y);
}

void Player::SetBinds(const PlayerBinds newBinds)
{
	this->binds = newBinds;
}

void Player::SetTeam(WORD team)
{
	this->team = team;
}

void Player::Update()
{
	UpdateInputState();
	UpdateVelocity();
	UpdatePosition();
}

void Player::UpdateInputState()
{
	if (Engine::IsKeyDown(binds.moveLeft))
		moveLeftState = true;
	else
		moveLeftState = false;

	if (Engine::IsKeyDown(binds.moveRight))
		moveRightState = true;
	else
		moveRightState = false;

	// 1 if we are moving right, -1 if we are moving left, and 0 if we are not moving, or pressing both directions at once.
	direction = moveRightState - moveLeftState;

	// Used to keep a direction to attack, even when not moving.
	if(direction != 0)
		lastDirection = direction;

	if(Engine::IsKeyDown(binds.jump))
		jumpState = true;
	else
		jumpState = false;

	if(Engine::IsKeyDown(binds.attack) && attackState == false)
	{
		attackState = true;
		TryAttack();
	}
	else
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

void Player::TryAttack()
{
	std::vector<Player*> players = Engine::GetInstance().GetGame().GetPlayers();

	Player* playerToAttack = nullptr;
	
	for (Player* const player : players)
	{
		// If we are moving right, check if the player is to our right, and within range.
		if(lastDirection == 1)
		{
			if(player->GetPosition().x > GetPosition().x && player->GetPosition().x < GetPosition().x + attackRange)
			{
				playerToAttack = player;
				break;
			}
		}
		else if(lastDirection == -1)
		{
			if(player->GetPosition().x < GetPosition().x && player->GetPosition().x > GetPosition().x - attackRange)
			{
				playerToAttack = player;
				break;
			}
		}
	}

	if (playerToAttack != nullptr)
		Attack(playerToAttack);
}

void Player::Attack(Player* player)
{
	exit(42);
}
