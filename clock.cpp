#include "clock.h"

Clock::Clock()
{
	startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
	lastSecond = startTime;
	fpsCount = 0;
}

bool Clock::updateTime() const
{
	return checkTime() >= lastSecond + 1000;
}

void Clock::update()
{
	fpsCount++;
	//if it has been one second since fps was last printed
	if (updateTime()) {
		printf("Frames per second: %d\n", fpsCount);
		lastSecond += 1000;
		fps = fpsCount;
		fpsCount = 0;
	}
}

double Clock::checkTime()
{
	const auto value = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch());
	return value.count();
}

void Clock::seedRand()
{
	srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count());
}
