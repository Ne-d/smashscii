#pragma once
#include "../Engine/Entity.h"
#include <map>
#include <Windows.h>

class Player : public Entity
{
public:

	void SetBind(WORD originalKeybind, WORD newKeybind);

private:
	std::map<WORD, void(*)()> binds;
};

