#pragma once

#include <chrono>
#include <Windows.h>

#include "Image.h"
#include "../Game/Player.h"
#include "../Game/Game.h"

class Engine
{
public: // Methods
	
	static Engine& GetInstance();

	void ShowTitle();
	void ShowEnd(int winner);
	void MainLoop();
	void WriteToBuffer(int x, int y, CHAR_INFO character) const;
	void Flush();
	void Clear() const;

	void SetScreenSize(unsigned int x, unsigned int y);
	
	void DrawImage(const Image& image, COORD coords) const;
	void DrawPlayer(const Player& player) const;
	void WriteText(const std::wstring& text, COORD coords, WORD attributes) const;

	float GetDeltaTime() const;
	Game& GetGame();

	static bool IsKeyDown(DWORD key);

	COORD GetScreenSize() const;
	void SetDwBufferSize(const COORD& dwBufferSize);

	void EndGame(int winner);

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

	Game game;
	bool isRunning = true;
};
