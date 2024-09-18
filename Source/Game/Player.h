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

	void SetBinds(const PlayerBinds& newBinds);
	void Update();

	void CheckInputs(std::vector<WORD>& inputQueueList);
	void UpdateInputState();

	//player action functions
	void MoveLeft();
	void MoveRight();

private:
	PlayerBinds binds;

	//action states
	bool moveLeftState;
	bool moveRightState;
};

