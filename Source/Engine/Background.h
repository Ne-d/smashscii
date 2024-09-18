#pragma once
#include "Image.h"

class Background
{
public:
	Background() = default;
	Background(COORD& size);
	~Background();

	const bool& GetCollisionTile(COORD& coords) const;
	void SetCollisionTile(COORD& coords, bool& collisionTileBool);

	Image& GetImage();

private:
	bool** collisionTable;
	Image image;
};
