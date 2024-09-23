#pragma once

#include <chrono>
#include <Windows.h>

#include "Image.h"
#include "../Game/Player.h"
#include "../Game/Game.h"

class Engine
{
public: // Methods
	static Engine* GetInstance();

	// Game phases
	void ShowTitle();
	void MainLoop();
	void EndGame(int winner);

	// Drawing to screen
	void WriteToBuffer(int x, int y, CHAR_INFO character) const;
	void Flush();
	void Clear() const;
	
	void DrawImage(const Image& image, COORD coords) const;
	void DrawPlayer(const Player& player) const;
	void WriteText(const std::wstring& text, COORD coords, WORD attributes) const;

	// Accessors
	Game& GetGame();
	float GetDeltaTime() const;
	COORD GetScreenSize() const;

	void SetScreenSize(unsigned int x, unsigned int y);
	void SetDwBufferSize(const COORD& dwBufferSize);

	static bool IsKeyDown(DWORD key);

private:
	// Singleton things
	Engine();
	static Engine* instance;
	~Engine();
	
	// Windows handles
	HANDLE hOutput;
	HANDLE hInput;

	// Console data
	COORD dwBufferSize;
	SMALL_RECT rcRegion;
	CHAR_INFO* buffer;

	// Frame timing
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	float frameTime;

	// Game-related variables
	Game game;
	bool isRunning = true;
};
