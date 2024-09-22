#include <iostream>
#include <thread>

#include "Engine.h"
#include "../Game/Game.h"

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
	frameTime(0.001)
{
	SetConsoleWindowInfo(hOutput, FALSE, &rcRegion);
}

COORD Engine::GetScreenSize() const
{
	return dwBufferSize;
}

void Engine::SetDwBufferSize(const COORD& dwBufferSize)
{
	this->dwBufferSize = dwBufferSize;
}

Engine& Engine::GetInstance()
{
	// TODO: Changer �a pour faire plaisir � Axel.
	static Engine instance;
	return instance;
}

void Engine::MainLoop()
{
	while (true)
	{
		begin = std::chrono::steady_clock::now();
		
        // INPUTS
		ReadInputs();
        
        // GAME CODE
		game.Update();
        
        // RENDERING
		Clear();
		
		for (const Player* player : game.GetPlayers())
			DrawPlayer(*player);

		Flush();

		// Chrono's duration cast only allows us to get an integral value with count()
		// so we do the conversion manually. 
		frameTime = (begin - end).count() / 1'000'000'000.f;
		
		end = begin;
	}
}

void Engine::WriteToBuffer(const unsigned int x, const unsigned int y, const CHAR_INFO character) const
{
	if(x < dwBufferSize.X && y < dwBufferSize.Y)
		buffer[x + y * dwBufferSize.X] = character;
}

void Engine::Flush()
{
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, {0, 0}, &rcRegion);
}

void Engine::Clear() const
{
	for (int y = 0; y < dwBufferSize.Y; y++)
	{
		for (int x = 0; x < dwBufferSize.X; x++)
			WriteToBuffer(x, y, {' ', 0x00});
	}
}

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

	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		{ 0, 0 }, &rcRegion);

	SetConsoleWindowInfo(hOutput, TRUE, &rcRegion);
}

void Engine::DrawImage(const Image& image, const COORD coords) const
{
	for (int y = 0; y < image.GetSize().Y; ++y)
	{
		for (int x = 0; x < image.GetSize().X; ++x)
		{
			WriteToBuffer(x + coords.X, y + coords.Y, image.GetChar(x, y));
		}
	}
}

void Engine::DrawPlayer(const Player& player) const
{
	DrawImage(player.GetImage(), player.GetPosition().RoundToCoord());
}

double Engine::GetDeltaTime() const
{
	return frameTime; // frameTime is in nanoseconds, we return milliseconds.
}

Game& Engine::GetGame()
{
	return game;
}

void Engine::ReadInputs()
{
	constexpr DWORD inputRecordSize = 255;
	INPUT_RECORD inputRecord[inputRecordSize];
	DWORD numberOfEventsRead;

	PeekConsoleInput(hInput, inputRecord, inputRecordSize, &numberOfEventsRead);
	if (numberOfEventsRead == 0)
		return;

	ReadConsoleInput(hInput, inputRecord, inputRecordSize, &numberOfEventsRead);

	keyCodeList.clear();

	for (unsigned int i = 0; i < numberOfEventsRead; ++i)
	{
		switch (inputRecord[i].EventType)
		{
		case KEY_EVENT:
			keyCodeList.push_back(inputRecord[i].Event.KeyEvent.wVirtualKeyCode);
			break;
		default:
			break;
		}
	}
}

std::vector<DWORD> Engine::GetInputs()
{
	return keyCodeList;
}

bool Engine::IsKeyDown(const DWORD key)
{
	// Shamelessly stolen from Frank S. at:
	// https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c

	return GetKeyState(key) & 0x8000; //Check if high-order bit is set (1 << 15)

	/* The suggested API (with ReadConsoleInput) seems to only count keys as pressed for a single frame,
	   then repeats automatically after a delay.
	   This is suitable for text input, but not continuous character movement.
	   Because of this, we use a different input system, that is still part of the Windows API. */
}
