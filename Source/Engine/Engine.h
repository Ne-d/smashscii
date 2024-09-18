#pragma once

#include <Windows.h>
#include "Image.h"

class Engine
{
public: // Methods
	Engine(unsigned int width, unsigned int height);

	void MainLoop();
	void WriteToBuffer(unsigned int x, unsigned int y, CHAR_INFO character);
	void Flush();
	
	void DrawImage(Image image, COORD coords);

private: // Data
	const HANDLE hOutput;
	const COORD dwBufferSize;
	SMALL_RECT rcRegion;

	CHAR_INFO* buffer;
};
