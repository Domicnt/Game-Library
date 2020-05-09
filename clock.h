#pragma once
#include <chrono>

class Clock {
public:
	//time since last reset / initialization
	double startTime;
	//frames per second
	int fps;
	int fpsCount;
	//the last time value that fpsCount was reset
	double lastSecond;

	//constructor
	Clock();

	//true after one second has passed
	bool updateTime() const;
	//increment fps or print and reset it; must be called every frame
	void update();
	//time, in milliseconds
	static double checkTime();
	//seeds rand() with time
	static void seedRand();
};