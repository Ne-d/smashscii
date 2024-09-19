#include "Background.h"

Background::Background(COORD& size)
	:
	image(size)
{
	this->collisionTable = new bool* [size.X];
	for (int i = 0; i < size.X; ++i)
	{
		this->collisionTable[i] = new bool[size.Y];
	}
}

Background::~Background()
{
	for (int i = 0; i < this->image.GetSize().X; ++i)
	{
		delete this->collisionTable[i];
	}

	delete this->collisionTable;
}

const bool& Background::GetCollisionTile(COORD& coords) const
{
	return this->collisionTable[coords.X][coords.Y];
}

void Background::SetCollisionTile(COORD& coords, bool& collisionTileBool)
{
	this->collisionTable[coords.X][coords.Y] = collisionTileBool;
}

Image& Background::GetImage()
{
	return this->image;
}