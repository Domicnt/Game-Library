#pragma once

#include "graphics.h"

class Camera
{
public:
	//position
	SDL_FPoint pos;
	//size of the window being rendered to
	int w, h;
	//magnification for everything
	float zoom;

	//get a point on screen from a point in the world
	SDL_FPoint projectPoint(SDL_FPoint point) const;
	//get a point in the world from a point on screen
	SDL_FPoint inverseProjectPoint(SDL_FPoint point) const;

	//check if a point would be visible on screen
	bool visible(const SDL_FPoint& point) const;
};