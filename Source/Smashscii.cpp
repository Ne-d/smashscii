// Smashscii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

#include "Engine/Engine.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 90

int main(void)
{
	Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	COORD imageSize = { 3, 3 };
	Image image(imageSize);
	image.setChar(0, 0, { ' ',  0x0E });
	image.setChar(1, 0, { 'O',  0x0E });
	image.setChar(2, 0, { ' ',  0x0E });
	image.setChar(0, 1, { '-',  0x0E });
	image.setChar(1, 1, { '|',  0x0E });
	image.setChar(2, 1, { '-',  0x0E });
	image.setChar(0, 2, { '/',  0x0E });
	image.setChar(1, 2, { ' ',  0x0E });
	image.setChar(2, 2, { '\\', 0x0E });

	engine.DrawImage(image, { 0, 0 });

	while (true)
	{
		engine.Flush();
	}
}