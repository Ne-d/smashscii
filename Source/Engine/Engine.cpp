#include <iostream>
#include <thread>

#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height)
	: 
	hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)),
	hInput((HANDLE)GetStdHandle(STD_INPUT_HANDLE)),
	dwBufferSize(COORD{ (short)width, (short)height }),

	timePoint(std::chrono::steady_clock::now()),
	previousTimePoint(std::chrono::steady_clock::now()),
	frameTime(std::chrono::milliseconds(1))
{
	rcRegion.Left = 0;
	rcRegion.Top = 0;
	rcRegion.Right = dwBufferSize.X - 1;
	rcRegion.Bottom = dwBufferSize.Y - 1;

	SetConsoleScreenBufferSize(hOutput, dwBufferSize);

	buffer = new CHAR_INFO[dwBufferSize.X * dwBufferSize.Y];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		{ 0, 0 }, &rcRegion);
}

void Engine::MainLoop()
{
	COORD imageSize = { 3, 3 };
	Image image(imageSize);
	image.SetChar(0, 0, { ' ',  0x0E });
	image.SetChar(1, 0, { 'O',  0x0E });
	image.SetChar(2, 0, { ' ',  0x0E });
	image.SetChar(0, 1, { '-',  0x0E });
	image.SetChar(1, 1, { '|',  0x0E });
	image.SetChar(2, 1, { '-',  0x0E });
	image.SetChar(0, 2, { '/',  0x0E });
	image.SetChar(1, 2, { ' ',  0x0E });
	image.SetChar(2, 2, { '\\', 0x0E });

	short x = 0;

	while (true)
	{
		timePoint = std::chrono::steady_clock::now();
		
        // INPUTS
		ReadInputs();
        
        // GAME CODE
        // For each player in the Game, call their update function
        
        // RENDERING
		Clear();

		DrawImage(image, { x, 0 });
		x++;
		x = x % 160;

		Flush();

        frameTime = (timePoint - previousTimePoint);
		//auto frameRate = 1000'000'000 / (std::chrono::duration_cast<std::chrono::nanoseconds>(frameTime).count());

		std::this_thread::sleep_until(timePoint + std::chrono::milliseconds(1));
		
		previousTimePoint = timePoint;
	}
}

void Engine::WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character)
{
	buffer[x + y * dwBufferSize.X] = character;
}

void Engine::Flush()
{
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, {0, 0}, &rcRegion);
}

void Engine::Clear()
{
	for (int y = 0; y < dwBufferSize.Y; y++)
	{
		for (int x = 0; x < dwBufferSize.X; x++)
			WriteToBuffer(x, y, {' ', 0x00});
	}
}

void Engine::DrawImage(const Image& image, COORD coords)
{
	for (int y = 0; y < image.GetSize().Y; ++y)
	{
		for (int x = 0; x < image.GetSize().X; ++x)
		{
			WriteToBuffer(x + coords.X, y + coords.Y, image.GetChar(x, y));
		}
	}
}

void Engine::ReadInputs()
{
	constexpr DWORD inputRecordSize = 255;
	INPUT_RECORD inputRecord[inputRecordSize];
	DWORD numberOfEventsRead;

	PeekConsoleInput(hInput, inputRecord, inputRecordSize, &numberOfEventsRead);
	if (numberOfEventsRead == 0)
		return;

	BOOL res = ReadConsoleInput(hInput, inputRecord, inputRecordSize, &numberOfEventsRead);

	keyEventList.clear();

	for (int i = 0; i < numberOfEventsRead; ++i)
	{
		switch (inputRecord[i].EventType)
		{
		case KEY_EVENT:
			keyEventList.push_back(inputRecord[i].Event.KeyEvent.wVirtualKeyCode);
			break;
		default:
			break;
		}

	}
}
