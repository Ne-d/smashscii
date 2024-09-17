#pragma once

#include <Windows.h>

class Engine
{
public:
	Engine(unsigned int width, unsigned int height);

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character);
	void Flush();

private:
	const HANDLE hOutput;
	const COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;
};

