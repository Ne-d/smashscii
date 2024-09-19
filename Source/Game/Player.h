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

	void UpdateInputState();
	void UpdatePosition();

private:
	PlayerBinds binds;

	// Action states
	bool moveLeftState;
	bool moveRightState;
};

