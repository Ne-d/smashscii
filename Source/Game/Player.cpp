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
	if (Engine::IsKeyDown(binds.moveLeftBind))
		moveLeftState = true;
	else
		moveLeftState = false;

	if (Engine::IsKeyDown(binds.moveRightBind))
		moveRightState = true;
	else
		moveRightState = false;

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
	if (moveLeftState && !moveRightState)
		velocity.x = Damp(velocity.x, -targetSpeed, walkAcceleration);

	else if (moveRightState && !moveLeftState)
		velocity.x = Damp(velocity.x, targetSpeed, walkAcceleration);

	else
		velocity.x = Damp(velocity.x, 0, stopAcceleration);

	velocity.y = Damp(velocity.y, gravitySpeed, gravityAcceleration);
}

void Player::ApplyBounds()
{
	const COORD screenSize = Engine::GetInstance().GetScreenSize();

	if(GetPosition().x + GetImage().GetSize().X >= screenSize.X && velocity.x > 0)
	{
		SetPosition(screenSize.X - GetImage().GetSize().X, GetPosition().y);
		velocity.x = 0;
	}

	if(GetPosition().x <= 0 && velocity.x < 0)
	{
		SetPosition(0, GetPosition().y);
		velocity.x = 0;
	}

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

void Player::FireProjectile()
{
	Vector2D projectileVelocity;
	if (isAimingRight)
		projectileVelocity = Vector2D(1.f * projectileSpeed, 0);
	else
		projectileVelocity = Vector2D(-1.f * projectileSpeed, 0);

	this->projectile.Fire(GetPosition(), projectileVelocity);
}
