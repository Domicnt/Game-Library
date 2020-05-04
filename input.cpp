#include "input.h"

Input::Input()
{	
	leftClick = false;
	rightClick = false;
	leftButton = false;
	rightButton = false;
}

bool Input::checkKey(const char* key)
{
	//create array of all keys' states
	const auto keystates = SDL_GetKeyboardState(nullptr);
	//check if the desired key is down
	if (keystates[SDL_GetKeyFromName(key)])
	{
		return true;
	}
	return false;
}

SDL_Point Input::getPos()
{
	int mX, mY;
	SDL_GetMouseState(&mX, &mY);
	return { mX, mY };
}

void Input::update(bool* quit)
{
	//push up new events
	SDL_PumpEvents();
	//reset click variables
	leftClick = false;
	rightClick = false;
	//while there are events yet to be processed
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			//the program is closed
		case SDL_QUIT:
			*quit = true;
			break;
			//mouse button pressed
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button) {
			//left button
			case SDL_BUTTON_LEFT:
				leftClick = true;
				leftButton = true;
				break;
			//right button
			case SDL_BUTTON_RIGHT:
				rightClick = true;
				rightButton = true;
				break;
			default:
				break;
			}
			break;
			//mouse button released
		case SDL_MOUSEBUTTONUP:
			switch (e.button.button) {
			//left button
			case SDL_BUTTON_LEFT:
				leftButton = false;
				break;
			//right button
			case SDL_BUTTON_RIGHT:
				rightButton = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}