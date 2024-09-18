#pragma once
#include <Windows.h>

class Image
{
public:

	Image() = default;
	Image(COORD& size);
	~Image();

	//CHAR_INFO** GetTable() const;
	const COORD& GetSize() const;

	void SetChar(int x, int y, CHAR_INFO character);
	const CHAR_INFO& GetChar(int x, int y) const;

private:
	CHAR_INFO** table;
	COORD size;
};

