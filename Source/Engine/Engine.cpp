#include <iostream>
#include <thread>

#include "Engine.h"
#include "../Game/Game.h"

Engine* Engine::instance = nullptr;

Engine::Engine()
	:
	hOutput(GetStdHandle(STD_OUTPUT_HANDLE)),
	hInput(GetStdHandle(STD_INPUT_HANDLE)),

	// Default size
	dwBufferSize({ 160, 90 }),
	rcRegion({0, 0, 160, 90}),
	buffer(new CHAR_INFO[160 * 90]),

	begin(std::chrono::steady_clock::now()),
	end(std::chrono::steady_clock::now()),
	frameTime(0.001f)
{
	SetConsoleWindowInfo(hOutput, FALSE, &rcRegion);
}

Engine::~Engine()
{
	delete[] buffer;
}

COORD Engine::GetScreenSize() const
{
	return dwBufferSize;
}

void Engine::SetDwBufferSize(const COORD& dwBufferSize)
{
	this->dwBufferSize = dwBufferSize;
}

void Engine::EndGame(const int winner)
{
	// Stop the main loop.
	isRunning = false;

	// Show end screen.
	Clear();
	game.DrawEnd();
	WriteText(L"Le joueur " + std::to_wstring(winner + 1) + L" a gagne !", COORD{49, 18}, 0x0e);
	Flush();

	// Wait for user input to close the window.
	// HACK: Busy wait.
	while(!IsKeyDown(VK_RETURN))
	{}
}

// Standard singleton stuff.
Engine* Engine::GetInstance()
{
	if(instance == nullptr)
		instance = new Engine();
	
	return instance;
}

void Engine::ShowTitle()
{
	// Draw title screen.
	Clear();
	game.DrawTitle();
	Flush();

	// Wait for user input to start the game.
	while(!IsKeyDown(VK_RETURN))
	{}

	// Start the game.
	isRunning = true;
	MainLoop();
}

void Engine::MainLoop()
{
	while (isRunning)
	{
		begin = std::chrono::steady_clock::now();

		Clear();
		game.DrawBackground();
        
        // GAME CODE
		game.Update();

		// Draw every player.
		for (const Player* player : game.GetPlayers())
			DrawPlayer(*player);
		
		Flush();

		// Chrono's duration cast only allows us to get an integral value with count()
		// so we do the conversion manually. 
		frameTime = (begin - end).count() / 1'000'000'000.f;
		
		end = begin;
	}
}

/**
 * Writes a character to the buffer.
 * @param x The x coordinate to write to.
 * @param y The y coordinate to write to.
 * @param character The CHAR_INFO to write. 
 */
void Engine::WriteToBuffer(const int x, const int y, const CHAR_INFO character) const
{
	if(x < dwBufferSize.X && y < dwBufferSize.Y)
		buffer[x + y * dwBufferSize.X] = character;
}

/**
 * Sends all data from the buffer to the actual console output.
 */
void Engine::Flush()
{
	WriteConsoleOutput(hOutput, buffer, dwBufferSize, {0, 0}, &rcRegion);
}

/**
 * Clears the buffer.
 */
void Engine::Clear() const
{
	for (int y = 0; y < dwBufferSize.Y; y++)
	{
		for (int x = 0; x < dwBufferSize.X; x++)
			WriteToBuffer(x, y, {' ', 0x00});
	}
}

/**
 * Change the size of the console window and the buffer.
 * @param x The new horizontal size.
 * @param y The new vertical size.
 */
void Engine::SetScreenSize(const unsigned int x, const unsigned int y)
{
	dwBufferSize.X = x;
	dwBufferSize.Y = y;
	
	rcRegion.Left = 0;
	rcRegion.Top = 0;
	rcRegion.Right = dwBufferSize.X - 1;
	rcRegion.Bottom = dwBufferSize.Y - 1;

	SetConsoleScreenBufferSize(hOutput, dwBufferSize);

	buffer = new CHAR_INFO[dwBufferSize.X * dwBufferSize.Y];

	ReadConsoleOutput(hOutput, buffer, dwBufferSize,
		{ 0, 0 }, &rcRegion);

	SetConsoleWindowInfo(hOutput, TRUE, &rcRegion);
}

/**
 * Draws an image to the buffer.
 * @param image The image to draw.
 * @param coords The coordinates to draw the image at (top right corner)
 */
void Engine::DrawImage(const Image& image, const COORD coords) const
{
	for (int y = 0; y < image.GetSize().Y; ++y)
	{
		for (int x = 0; x < image.GetSize().X; ++x)
			WriteToBuffer(x + coords.X, y + coords.Y, image.GetChar(x, y));
	}
}

/**
 * Draws a player to the buffer.
 * @param player The player to draw.
 */
void Engine::DrawPlayer(const Player& player) const
{
	DrawImage(player.GetImage(), player.GetPosition().RoundToCoord());
}

/**
 * Writes a string to the buffer.
 * @param text The string to write.
 * @param coords The coordinates to write at.
 * @param attributes The usual CHAR_INFO attributes (color, etc.). 
 */
void Engine::WriteText(const std::wstring& text, const COORD coords, const WORD attributes) const
{
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		WriteToBuffer(coords.X + i, coords.Y, CHAR_INFO{text.at(i), attributes});
	}
}

/**
 * @return The time that the last frame lasted.
 */
float Engine::GetDeltaTime() const
{
	return frameTime; // frameTime is in nanoseconds, we return milliseconds.
}

Game& Engine::GetGame()
{
	return game;
}

bool Engine::IsKeyDown(const DWORD key)
{
	// Shamelessly stolen from Frank S. at:
	// https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c

	return (GetKeyState(key) & 0x8000) != 0; //Check if high-order bit is set (1 << 15)

	/* The suggested API (with ReadConsoleInput) seems to only count keys as pressed for a single frame,
	   then repeats automatically after a delay.
	   This is suitable for text input, but not continuous character movement.
	   Because of this, we use a different input system, that is still part of the Windows API. */
}
