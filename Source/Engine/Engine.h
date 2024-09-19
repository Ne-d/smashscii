#pragma once

#include <chrono>
#include <vector>
#include <Windows.h>

#include "Image.h"
#include "../Game/Player.h"

class Engine
{
public: // Methods
	
static Engine& GetInstance();

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character) const;
	void Flush();
	void Clear() const;

	void SetScreenSize(unsigned int x, unsigned int y);
	
	void DrawImage(const Image& image, COORD coords) const;
	void DrawPlayer(const Player& player);

	double GetDeltaTime() const;

	void ReadInputs();
	std::vector<DWORD> GetInputs();

	static bool IsKeyDown(DWORD key);

private: // Constructor, because Singleton
	Engine();

	// Data
	HANDLE hOutput;
	HANDLE hInput;

	COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;

	std::chrono::steady_clock::time_point timePoint;
	std::chrono::steady_clock::time_point previousTimePoint;
	std::chrono::nanoseconds frameTime;

	std::vector<DWORD> keyCodeList;
};
