#include "Image.h"
#include <fstream>

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

Image::Image(std::string filename, WORD color) : size(GetFileSize(filename)), table(new CHAR_INFO* [size.X])
{
	for (int i = 0; i < size.X; ++i)
	{
		this->table[i] = new CHAR_INFO[size.Y];
	}
	LoadFromFile(filename, color);
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

COORD Image::GetFileSize(std::string filename)
{
	std::fstream fstrm(filename);
	COORD fileSize;
	std::string fileLine;
	while (std::getline(fstrm, fileLine))
	{
		++fileSize.X;
	}
	fileSize.Y = fileLine.length() - 1;

	return fileSize;
}

void Image::LoadFromFile(std::string filename, WORD color)
{
	std::fstream fstrm(filename);
	std::string fileLine;
	int lineCount = 0;
	while (std::getline(fstrm, fileLine))
	{
		for (int i = 0; i < fileLine.length() - 1; ++i)
		{
			std::wstring wfileLine = std::wstring(fileLine.begin(), fileLine.end());
			this->table[lineCount][i] = { wfileLine[i],  color};
		}
		++lineCount;
	}
}
