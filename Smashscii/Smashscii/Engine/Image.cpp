#include "Image.h"

Image::Image(COORD& size)
{
	this->table = new CHAR_INFO * [size.X];

	for (int i = 0; i < size.X; ++i)
	{
		this->table[i] = new CHAR_INFO[size.Y];
	}

	this->size = size;
}

const CHAR_INFO** Image::GetTable() const
{
	return this->table;
}

const COORD& Image::GetSize() const
{
	return this->size;
}