#pragma once
#include <chrono>

class Clock {
public:
	//time since last reset / initialization
	long float startTime;
	//frames per second
	int fps;
	//the last time value that fps was reset
	long float lastSecond;

	//constructor
	Clock();
	
	//increment fps or print and reset it; must be called every frame
	void update();
	//time, in milliseconds
	static long float checkTime();
	//seeds rand() with time
	static void seedRand();
};