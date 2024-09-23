#include "Image.h"
#include <fstream>

/**
 * Creates an empty image of a given size.
 * @param size The size of the image.
 */
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

/**
 * Creates an image, whose contents are loaded from a file.
 * The dimensions of the image are determined automatically from the file's contents.
 * Only use files whose contents are in the shape of a rectangle (including whitespace).
 * @param filename The file to load the image from.
 * @param color The attributes determining the color of the image.
 */
Image::Image(const std::string& filename, const WORD color) : size(GetFileDimensions(filename)), table(new CHAR_INFO* [size.X])
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

/**
 * Finds the dimensions of the contents of a file, if it is a rectangle.
 * @param filename The file to analyse.
 * @return The dimensions of the file's contents.
 * @note DO NOT USE with files whose contents are not in the shape of a rectangle (including whitespace).
 */
COORD Image::GetFileDimensions(const std::string& filename)
{
	std::fstream stream(filename);
	COORD dimensions{0, 0};
	std::string line;
	
	while (std::getline(stream, line))
	{
		++dimensions.Y;
	}
	
	dimensions.X = line.length();

	return dimensions;
}

/**
 * Loads the contents of a file and puts it in this image.
 * @param filename The file to load the contents of.
 * @param color The attributes determining the color of the image.
 */
void Image::LoadFromFile(const std::string& filename, const WORD color) const
{
	std::fstream stream(filename);
	std::string line;
	int lineCount = 0;
	while (std::getline(stream, line))
	{
		for (unsigned int i = 0; i < line.length(); ++i)
			this->table[i][lineCount] = CHAR_INFO{ static_cast<WCHAR>(line.at(i)),  color};
		
		++lineCount;
	}
}