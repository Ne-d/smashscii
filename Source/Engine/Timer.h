// Adapted from the Enjmin C++ course.

#pragma once

#include <windows.h>

class Timer
{
public:
	Timer();
	
	void Start();
	
	float GetElapsedSeconds(bool restart = false);

	unsigned long GetElapsedMs(bool restart = false) const;

private:
	LARGE_INTEGER lastUpdateTime;
	LONGLONG freq;
};
