#pragma once

#include <Windows.h>
#include <chrono>
#include <vector>

#include "Image.h"

class Engine
{
public: // Methods
	Engine(unsigned int width, unsigned int height);

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character);
	void Flush();
	void Clear();
	
	void DrawImage(const Image& image, COORD coords);

	void ReadInputs();

private: // Data
	const HANDLE hOutput;
	const HANDLE hInput;

	const COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;

	std::chrono::steady_clock::time_point timePoint;
	std::chrono::steady_clock::time_point previousTimePoint;
	std::chrono::nanoseconds frameTime;

	std::vector<DWORD> keyEventList;
};
