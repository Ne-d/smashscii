#pragma once
#include "Image.h"

class Background
{
public:
	Background() = delete;
	explicit Background(const COORD& size);
	Background(const std::string& imageFilename, const std::string& collisionFilename, WORD color);
	~Background();

	const bool& GetCollisionTile(const COORD& coords) const;
	void SetCollisionTile(const COORD& coords, const bool& collisionTileBool) const;

	void LoadCollisionFromFile(const std::string& collisionFilename) const;

	Image& GetImage();

private:
	bool** collisionTable;
	Image image;
};
