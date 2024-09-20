#include "Background.h"
#include <fstream>

Background::Background(COORD& size) : image(Image(size)), collisionTable(new bool* [size.X])
{
	for (int i = 0; i < size.X; ++i)
	{
		this->collisionTable[i] = new bool[size.Y];
	}
}

Background::Background(std::string imageFilename, std::string collisionFilename, WORD color) : image(Image(imageFilename, color)), collisionTable(new bool* [image.GetSize().X])
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

	delete this->collisionTable;
}

const bool& Background::GetCollisionTile(COORD& coords) const
{
	return this->collisionTable[coords.X][coords.Y];
}

void Background::SetCollisionTile(COORD& coords, bool& collisionTileBool)
{
	this->collisionTable[coords.X][coords.Y] = collisionTileBool;
}

void Background::LoadCollisionFromFile(std::string collisionFilename)
{
	std::fstream fstrm(collisionFilename);
	std::string fileLine;
	int lineCount = 0;
	while (std::getline(fstrm, fileLine))
	{
		for (int i = 0; i < fileLine.length() - 1; ++i)
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
