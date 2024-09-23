#include "Background.h"
#include <fstream>

Background::Background(const COORD& size)
	:
	collisionTable(new bool* [static_cast<unsigned long long>(size.X)]),
	image(Image(size))
{
	for (int i = 0; i < size.X; ++i)
	{
		this->collisionTable[i] = new bool[static_cast<unsigned long long>(size.Y)];
	}
}

Background::Background(const std::string& imageFilename, const std::string& collisionFilename, const WORD color)
	:
	collisionTable(new bool* [static_cast<unsigned long long>(image.GetSize().X)]),
	image(Image(imageFilename, color))
{
	for (int i = 0; i < image.GetSize().X; ++i)
	{
		this->collisionTable[i] = new bool[static_cast<unsigned long long>(image.GetSize().Y)];
	}

	LoadCollisionFromFile(collisionFilename);
}

Background::~Background()
{
	for (int i = 0; i < this->image.GetSize().X; ++i)
	{
		delete this->collisionTable[i];
	}

	delete[] this->collisionTable;
}

const bool& Background::GetCollisionTile(const COORD& coords) const
{
	return this->collisionTable[coords.X][coords.Y];
}

void Background::SetCollisionTile(const COORD& coords, const bool& collisionTileBool) const
{
	this->collisionTable[coords.X][coords.Y] = collisionTileBool;
}

void Background::LoadCollisionFromFile(const std::string& collisionFilename) const
{
	std::fstream collisionFileStream(collisionFilename);
	std::string fileLine;
	int lineCount = 0;
	while (std::getline(collisionFileStream, fileLine))
	{
		for (unsigned int i = 0; i < fileLine.length(); ++i)
		{
			if (fileLine[i] != ' ')
			{
				this->collisionTable[lineCount][i] = true;
			}
			else {
				this->collisionTable[lineCount][i] = false;
			}
		}
		++lineCount;
	}
}

Image& Background::GetImage()
{
	return this->image;
}
