#include "Image.h"

Image::Image(const COORD& size)
	:
	table(new CHAR_INFO * [size.X]),
	size(size)
{
	for (int i = 0; i < size.X; ++i)
	{
		this->table[i] = new CHAR_INFO[size.Y];
	}
}

Image::~Image()
{
	for (int i = 0; i < this->size.X; ++i)
	{
		delete[] this->table[i];
	}

	delete[] this->table;
}

const CHAR_INFO& Image::GetChar(const int x, const int y) const
{
	return this->table[x][y];
}

const COORD& Image::GetSize() const
{
	return this->size;
}

void Image::SetChar(const int x, const int y, const CHAR_INFO character)
{
	table[x][y] = character;
}
