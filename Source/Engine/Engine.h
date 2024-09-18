#pragma once

#include <Windows.h>
#include <chrono>
#include <vector>

#include "Image.h"

class Engine
{
public: // Methods
	
static Engine& getInstance();

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character);
	void Flush();
	void Clear();

	void SetScreenSize(unsigned int x, unsigned int y);
	
	void DrawImage(const Image& image, COORD coords);

	void ReadInputs();
	std::vector<DWORD> GetInputs();

private: // Constructor, because Singleton
	Engine();

private: // Data
	const HANDLE hOutput;
	const HANDLE hInput;

	COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;

	std::chrono::steady_clock::time_point timePoint;
	std::chrono::steady_clock::time_point previousTimePoint;
	std::chrono::nanoseconds frameTime;

	std::vector<DWORD> keyCodeList;
};
