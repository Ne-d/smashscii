#pragma once
#include "Image.h"

class Background
{
public:
	Background() = default;
	Background(COORD& size);

	const bool** GetCollisionTable();
	const CHAR_INFO** GetImageTable();
	const COORD& GetImageSize();

private:
	bool** collisionTable;
	Image image;
};

