#include "Player.h"
#include <utility>

Player::Player(PlayerBinds& playerBinds)
	:
	moveLeftState(false),
	moveRightState(false),
	binds({0x41, 0x44}) // A and D keys (or Q and D on azerty)
{
}

void Player::SetBinds(const PlayerBinds& newBinds)
{
	this->binds = newBinds;
}

void Player::Update()
{
	UpdateInputState();
}

void Player::UpdateInputState()
{

}

void MoveLeft()
{

}

void MoveRight()
{

}