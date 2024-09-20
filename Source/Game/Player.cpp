#include "Player.h"

#include <iostream>

#include "../Engine/Engine.h"

Player::Player(const float x, const float y, const PlayerBinds binds, const WORD team)
	:
	Entity(Vector2D(x, y), "Player.txt", team),
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

void Player::UpdatePosition()
{
	const double frameTime = Engine::GetInstance().GetDeltaTime();
	
	if (moveLeftState && !moveRightState)
	{
		const Vector2D direction(-100, 0);
		Move(direction * frameTime);
	}

	if (moveRightState && !moveLeftState)
	{
		const Vector2D direction(100, 0);
		Move(direction * frameTime);
	}
}
