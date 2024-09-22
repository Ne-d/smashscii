#include "Background.h"
#include <fstream>

Background::Background(COORD& size) : image(Image(size)), collisionTable(new bool* [size.X])
{
	for (int i = 0; i < size.X; ++i)
	{
		this->collisionTable[i] = new bool[size.Y];
	}
}

Background::Background(const std::string& imageFilename, const std::string& collisionFilename, const WORD color)
	:
	collisionTable(new bool* [image.GetSize().X]),
	image(Image(imageFilename, color))
{
	for (int i = 0; i < image.GetSize().X; ++i)
	{
		this->collisionTable[i] = new bool[image.GetSize().Y];
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
	std::fstream fstrm(collisionFilename);
	std::string fileLine;
	int lineCount = 0;
	while (std::getline(fstrm, fileLine))
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
