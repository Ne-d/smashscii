#include "Player.h"
#include <utility>

Player::Player(PlayerBinds& playerBinds)
{
	this->binds.insert({ playerBinds.moveLeftBind, [this]() { MoveLeft(); } });
	this->binds.insert({ playerBinds.moveRightBind, [this]() { MoveRight(); } });
}

void Player::SetBind(WORD originalKeybind, WORD newKeybind)
{
	std::pair< WORD, std::function<void()>> keybind;

	bool foundKeybind = false;

	for (auto i : this->binds)
	{
		if (i.first == originalKeybind)
		{
			keybind = i;
			foundKeybind = true;
			break;
		}
	}

	if (foundKeybind)
	{
		this->binds.erase(keybind.first);
		this->binds.insert({newKeybind, keybind.second});
	}

}

void MoveLeft()
{

}

void MoveRight()
{

}