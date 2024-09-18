#include "Background.h"

Background::Background(COORD& size)
{

	this->image = Image(size);

	this->collisionTable = new bool* [size.X];
	for (int i = 0; i < size.X; ++i)
	{
		collisionTable[i] = new bool[size.Y];
	}
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