#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height)
	: hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)),
	dwBufferSize(COORD{ (short)width, (short)height})
{
	rcRegion.Left = 0;
	rcRegion.Top = 0;
	rcRegion.Right = dwBufferSize.X - 1;
	rcRegion.Bottom = dwBufferSize.Y - 1;

	buffer = new CHAR_INFO[dwBufferSize.X * dwBufferSize.Y];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		{ 0, 0 }, &rcRegion);

	WriteToBuffer(5, 10, {'H', 0x0E});
	WriteToBuffer(5, 11, { 'i', 0x0E });
	WriteToBuffer(5, 12, { 'H', 0x0E });
}

void Engine::WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character)
{
	buffer[x + y * dwBufferSize.X] = character;
}

void Engine::Flush()
{
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, {0, 0}, &rcRegion);
}
