#pragma once
#include <Windows.h>

class Image
{
public:

	Image() = default;
	Image(COORD& size);

	const CHAR_INFO** GetTable() const;
	const COORD& GetSize() const;

private:
	CHAR_INFO** table;
	COORD size;
};

