#include "clock.h"

Clock::Clock()
{
	startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
	lastSecond = startTime;
	fps = 0;
}

void Clock::update()
{
	fps++;
	//if it has been one second since fps was last printed
	if (checkTime() >= lastSecond + 1000) {
		printf("Frames per second: %d\n", fps);
		lastSecond += 1000;
		fps = 0;
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
