#include "Image.h"
#include <fstream>

Image::Image(const COORD& size)
	:
	size(size),
	table(new CHAR_INFO * [static_cast<unsigned int>(size.X)])
{
	for (int i = 0; i < size.X; ++i)
	{
		this->table[i] = new CHAR_INFO[static_cast<unsigned int>(size.Y)];
	}
}

Image::Image(const std::string& filename, const WORD color) : size(GetFileSize(filename)), table(new CHAR_INFO* [size.X])
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

void Image::SetChar(const int x, const int y, const CHAR_INFO character) const
{
	table[x][y] = character;
}

COORD Image::GetFileSize(const std::string& filename)
{
	std::fstream fstrm(filename);
	COORD fileSize{0, 0};
	std::string fileLine;
	
	while (std::getline(fstrm, fileLine))
	{
		++fileSize.Y;
	}
	
	fileSize.X = fileLine.length();

	return fileSize;
}

void Image::LoadFromFile(const std::string& filename, const WORD color) const
{
	std::fstream fstrm(filename);
	std::string fileLine;
	int lineCount = 0;
	while (std::getline(fstrm, fileLine))
	{
		for (unsigned int i = 0; i < fileLine.length(); ++i)
		{
			std::wstring wfileLine = std::wstring(fileLine.begin(), fileLine.end());
			this->table[i][lineCount] = CHAR_INFO{ static_cast<WCHAR>(fileLine.at(i)),  color};
		}
		++lineCount;
	}
}