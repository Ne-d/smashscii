#pragma once

#include <chrono>
#include <vector>
#include <Windows.h>

#include "Image.h"
#include "../Game/Player.h"
#include "../Game/Game.h"

class Engine
{
public: // Methods
	
	static Engine& GetInstance();
	
	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character) const;
	void Flush();
	void Clear() const;

	void SetScreenSize(unsigned int x, unsigned int y);
	
	void DrawImage(Image& image, COORD coords) const;
	void DrawPlayer(Player& player) const;
	void WriteText(const std::wstring& text, COORD coords, WORD attributes) const;

	float GetDeltaTime() const;
	Game& GetGame();

	void ReadInputs();
	std::vector<DWORD> GetInputs();

	static bool IsKeyDown(DWORD key);

	COORD GetScreenSize() const;
	void SetDwBufferSize(const COORD& dwBufferSize);

private:
	Engine(); // Constructor is private, because Singleton thingies.

	// Data
	HANDLE hOutput;
	HANDLE hInput;

	COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	float frameTime;

	std::vector<DWORD> keyCodeList;

	Game game;
};
