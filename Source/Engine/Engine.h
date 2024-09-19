#pragma once

#include <Windows.h>
#include <chrono>
#include <vector>

#include "Image.h"
#include "../Game/Player.h"

class Engine
{
public: // Methods
	
static Engine& GetInstance();

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character);
	void Flush();
	void Clear();

	void SetScreenSize(unsigned int x, unsigned int y);
	
	void DrawImage(const Image& image, COORD coords);
	void DrawPlayer(const Player& player);

	double GetDeltaTime();

	void ReadInputs();
	std::vector<DWORD> GetInputs();

	static bool IsKeyDown(DWORD key);

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
