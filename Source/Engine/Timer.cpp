// Adapted from the Enjmin C++ course.

#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceCounter(&lastUpdateTime);
	LARGE_INTEGER li_freq;
	QueryPerformanceFrequency(&li_freq);
	freq = li_freq.QuadPart;
	freq /= 1000;
}

void Timer::Start()
{
	QueryPerformanceCounter(&lastUpdateTime);
}

float Timer::GetElapsedSeconds(const bool restart)
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	const LONGLONG elapsedLong = timeNow.QuadPart-lastUpdateTime.QuadPart;

	float elapsed = (float) (static_cast<float>(elapsedLong)/static_cast<float>(freq));
	elapsed /= 1000.0f;

	if (restart)
		lastUpdateTime = timeNow;

	return elapsed;
}

unsigned long Timer::GetElapsedMs(bool restart) const
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	const LONGLONG elapsedLong = timeNow.QuadPart-lastUpdateTime.QuadPart;

	const unsigned long elapsed = static_cast<unsigned long>(static_cast<float>(elapsedLong) / static_cast<float>(freq));
	return elapsed;
}
