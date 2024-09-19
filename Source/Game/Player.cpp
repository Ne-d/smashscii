#include "Player.h"
#include "../Engine/Engine.h"

Player::Player(const unsigned int x, const unsigned int y, const PlayerBinds binds, const WORD team)
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
