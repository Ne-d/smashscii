#pragma once
#include <Windows.h>
#include <string>

class Image
{
public:
	// Constructors
	Image() = delete;
	explicit Image(const COORD& size);
	Image(const std::string& filename, WORD color);
	~Image();

	// Accessors
	const COORD& GetSize() const;
	void SetChar(int x, int y, CHAR_INFO character) const;
	const CHAR_INFO& GetChar(int x, int y) const;

	// Loading from file
	void LoadFromFile(const std::string& filename, WORD color) const;
	static COORD GetFileDimensions(const std::string& filename);

private: // Data
	COORD size;
	CHAR_INFO** table;
};

