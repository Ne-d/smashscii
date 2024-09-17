#pragma once
#include <windows.h>
#include "Image.h"

class Sprite
{
public:
	Sprite() = default;
	Sprite(COORD& size);

	const CHAR_INFO** GetImageTable();
	const COORD& GetImageSize();

private:
	Image image;
};

