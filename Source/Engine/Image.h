#pragma once
#include <Windows.h>

class Image
{
public:

	Image() = default;
	Image(COORD& size);

	CHAR_INFO** GetTable() const;
	const COORD& GetSize() const;

private:
	CHAR_INFO** table;
	COORD size;
};

