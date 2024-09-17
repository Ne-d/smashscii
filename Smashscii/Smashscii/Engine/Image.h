#pragma once
#include <Windows.h>

class Image
{
public:

	Image() = default;
	Image(COORD& size);

	const CHAR_INFO** GetTable();
	const COORD& GetSize();

private:
	CHAR_INFO** table;
	COORD size;
};

