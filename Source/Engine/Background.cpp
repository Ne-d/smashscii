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

bool** Background::GetCollisionTable() const
{
	return this->collisionTable;
}

CHAR_INFO** Background::GetImageTable() const
{
	return this->image.GetTable();
}

const COORD& Background::GetImageSize() const
{
	return this->image.GetSize();
}