#pragma once
#include <Windows.h>
#include <string>

class Image
{
public:

	Image() = delete;
	explicit Image(const COORD& size);
	Image(const std::string& filename, WORD color);
	~Image();

	//CHAR_INFO** GetTable() const;
	const COORD& GetSize() const;

	void SetChar(int x, int y, CHAR_INFO character) const;
	const CHAR_INFO& GetChar(int x, int y) const;

	void LoadFromFile(const std::string& filename, WORD color) const;
	static COORD GetFileSize(const std::string& filename);

private:
	COORD size;
	CHAR_INFO** table;
};

