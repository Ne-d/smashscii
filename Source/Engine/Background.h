#pragma once
#include "Image.h"

class Background
{
public:
	Background() = delete;
	Background(COORD& size);
	Background(std::string imageFilename, std::string collisionFilename, WORD color);
	~Background();

	const bool& GetCollisionTile(COORD& coords) const;
	void SetCollisionTile(COORD& coords, bool& collisionTileBool);

	void LoadCollisionFromFile(std::string collisionFilename);

	Image& GetImage();

private:
	bool** collisionTable;
	Image image;
};
