#pragma once
#include "vcpkg/installed/x86-windows/include/SDL2/SDL.h"

class Input
{
public:
	//SDL event handler
	SDL_Event e;

	//if mouse was pressed
	bool leftClick, rightClick;
	//if mouse is held
	bool leftButton, rightButton;

	Input();

	//check if a specific key is down
	static bool checkKey(char key);
	//get mouse position
	static SDL_Point getPos();
	//update based on inputs
	void update(bool* quit);
};