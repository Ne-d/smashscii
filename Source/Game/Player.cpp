#include <utility>
#include <iostream>

#include "Player.h"
#include "../Engine/Engine.h"

Player::Player(PlayerBinds& playerBinds)
	:
	moveLeftState(false),
	moveRightState(false)
{
	binds.moveLeftBind = 0x41;  // Q
	binds.moveRightBind = 0x44; // D
}

void Player::SetBinds(const PlayerBinds& newBinds)
{
	this->binds = newBinds;
}

void Player::Update()
{
	UpdateInputState();
	UpdatePosition();
}

void Player::UpdateInputState()
{
	std::vector<DWORD> keyCodeList = Engine::GetInstance().GetInputs();

	for (DWORD& keyCode : keyCodeList)
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
}

void Player::UpdatePosition()
{
	if (moveLeftState && !moveRightState)
	{
		Vector2D direction(-1, 0);
		Move(direction);
	}

	if (moveRightState && !moveLeftState)
	{
		Vector2D direction(1, 0);
		Move(direction);
	}
}