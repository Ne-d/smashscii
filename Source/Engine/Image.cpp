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

Image::~Image()
{
	for (int i = 0; i < this->size.X; ++i)
	{
		delete this->table[i];
	}

	delete this->table;
}

const CHAR_INFO& Image::GetChar(int x, int y) const
{
	return this->table[x][y];
}

const COORD& Image::GetSize() const
{
	return this->size;
}

void Image::SetChar(int x, int y, CHAR_INFO character)
{
	table[x][y] = character;
}
