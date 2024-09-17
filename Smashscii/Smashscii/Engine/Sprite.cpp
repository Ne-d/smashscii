#include "Sprite.h"

Sprite::Sprite(COORD& size)
{
	this->image = Image(size);
}

const CHAR_INFO** Sprite::GetImageTable()
{
	return this->image.GetTable();
}

const COORD& Sprite::GetImageSize()
{
	return this->image.GetSize();
}