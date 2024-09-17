#pragma once
#include "Image.h"

class Background
{
public:
	Background() = default;
	Background(COORD& size);

	bool** GetCollisionTable() const;
	CHAR_INFO** GetImageTable() const;
	const COORD& GetImageSize() const;

private:
	bool** collisionTable;
	Image image;
};

