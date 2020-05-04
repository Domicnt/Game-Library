#pragma once
#include <chrono>

class Clock {
public:
	//time since last reset / initialization
	double startTime;
	//frames per second
	int fps;
	//the last time value that fps was reset
	double lastSecond;

	//constructor
	Clock();
	
	//increment fps or print and reset it; must be called every frame
	void update();
	//time, in milliseconds
	static double checkTime();
	//seeds rand() with time
	static void seedRand();
};