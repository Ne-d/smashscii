#include <iostream>
#include <thread>

#include "Engine.h"
#include "../Game/Game.h"

Engine::Engine()
	:
	hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)),
	hInput((HANDLE)GetStdHandle(STD_INPUT_HANDLE)),

	timePoint(std::chrono::steady_clock::now()),
	previousTimePoint(std::chrono::steady_clock::now()),
	frameTime(std::chrono::milliseconds(1)),

	// Default size
	dwBufferSize({ 160, 90 }),
	rcRegion({0, 0, 160, 90}),
	buffer(new CHAR_INFO[160 * 90])
{
	
}

Engine& Engine::GetInstance()
{
	static Engine instance;
	return instance;
}

void Engine::MainLoop()
{
	Game game;

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
		game.Update();
        
        // RENDERING
		Clear();

		/*DrawImage(image, {x, 0});
		x++;
		x = x % 160;
		*/

		for (const Player& player : game.GetPlayers())
			DrawPlayer(player);

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

void Engine::SetScreenSize(unsigned int x, unsigned int y)
{
	rcRegion.Left = 0;
	rcRegion.Top = 0;
	rcRegion.Right = dwBufferSize.X - 1;
	rcRegion.Bottom = dwBufferSize.Y - 1;

	dwBufferSize.X = x;
	dwBufferSize.Y = y;

	SetConsoleScreenBufferSize(hOutput, dwBufferSize);

	buffer = new CHAR_INFO[dwBufferSize.X * dwBufferSize.Y];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		{ 0, 0 }, &rcRegion);
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

void Engine::DrawPlayer(const Player& player)
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

	DrawImage(image, player.GetPosition().RoundToCoord());
	
	/*std::cout << "Player coordinates: " << player.GetPosition().x << " (" << player.GetPosition().RoundToCoord().X << "), "
		<< player.GetPosition().y << " (" << player.GetPosition().RoundToCoord().Y << ")"
		<< std::endl;*/
}

double Engine::GetDeltaTime()
{
	return frameTime.count() / 1'000'000.0; // frameTime is in nanoseconds, we return milliseconds.
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

bool Engine::IsKeyDown(DWORD key)
{
	// Shamelessly stolen from Frank S. at:
	// https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c

	return GetKeyState(key) & 0x8000; //Check if high-order bit is set (1 << 15)

	// The suggested API with (ReadConsoleInput) seems to only count keys as pressed for a single frame,
	// then repeats automatically after a delay.
	// This is suitable for text input, but not continuous character movement.
	// Therefore we use a different input system, that is still part of the Windows API.
}
