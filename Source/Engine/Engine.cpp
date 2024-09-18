#include <iostream>
#include <thread>

#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height)
	: hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)),
	dwBufferSize(COORD{ (short)width, (short)height })
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
		auto lastTime = std::chrono::steady_clock::now();
		Clear();

		DrawImage(image, { x, 0 });
		x++;
		x = x % 160;

		Flush();

		auto currentTime = std::chrono::steady_clock::now();
		auto frameTime = currentTime - lastTime;
		auto frameRate = 100'000'000 / (std::chrono::duration_cast<std::chrono::nanoseconds>(frameTime).count());

		std::cout << frameRate << std::endl;

		//std::this_thread::sleep_until(lastTime + std::chrono::milliseconds(16));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

void Engine::DrawImage(Image image, COORD coords)
{
	for (int y = 0; y < image.GetSize().Y; y++)
	{
		for (int x = 0; x < image.GetSize().X; x++)
		{
			WriteToBuffer(x + coords.X, y + coords.Y, image.GetTable()[x][y]);
		}
	}
}
