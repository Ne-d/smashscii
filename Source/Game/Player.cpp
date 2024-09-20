#include "Player.h"

#include <cmath>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team)
	:
	Entity(COORD{ 3, 3 }, Vector2D(x, y)),
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
}

// Shamelessly stolen from https://www.febucci.com/2018/08/easing-functions/.
float Lerp(const float startValue, const float endValue, const float factor)
{
	return startValue + (endValue - startValue) * factor;
}

// Adapted from from https://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/.
float Damp(float startValue, float endValue, float lambda)
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
}

void Player::UpdatePosition()
{
	Move(velocity * Engine::GetInstance().GetDeltaTime());
}
