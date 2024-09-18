#include "Player.h"
#include <utility>

void Player::SetBind(WORD originalKeybind, WORD newKeybind)
{
	std::pair< WORD, void(*)() > keybind;

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