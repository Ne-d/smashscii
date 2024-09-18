// Smashscii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#include "Engine/Engine.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 90

int main(void)
{
	Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);

	engine.MainLoop();
}
