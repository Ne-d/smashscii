#pragma once
#include <Windows.h>
#include <string>

class Image
{
public:

	Image() = delete;
	explicit Image(const COORD& size);
	Image(std::string filename, WORD color);
	~Image();

	//CHAR_INFO** GetTable() const;
	const COORD& GetSize() const;

	void SetChar(int x, int y, CHAR_INFO character);
	const CHAR_INFO& GetChar(int x, int y) const;

	void LoadFromFile(std::string filename, WORD color);
	COORD GetFileSize(std::string filename);

	bool CheckVisibility();

	void Hide();
	void Show();

private:
	CHAR_INFO** table;
	COORD size;

	bool isVisible = true;
};

