#pragma once
#include "../Engine/Entity.h"
#include <map>
#include <Windows.h>
#include <vector>
#include <functional>


struct PlayerBinds
{
	WORD moveLeftBind;
	WORD moveRightBind;
};

class Player : public Entity
{
public:
	Player() = default;
	Player(PlayerBinds& playerBinds);

	void SetBind(WORD originalKeybind, WORD newKeybind);

	void CheckInputs(std::vector<WORD>& inputQueueList);

	//player action functions
	void MoveLeft();
	void MoveRight();

private:
	std::map<WORD, std::function<void()>> binds;

	//action states
	bool moveLeftState;
	bool moveRightState;
};

