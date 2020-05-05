#pragma once

#include "vcpkg/installed/x86-windows/include/SDL2/SDL.h"

class Camera
{
public:
	//position
	SDL_FPoint pos;
	//size of the window being rendered to
	int w, h;
	//scaling for physics objects
	float scaling;
	//magnification for everything
	float zoom;

	//constructor
	Camera() = default;
	Camera(const int& W, const int& H, const float& Scaling);
	
	//get a point on screen from a point in the world
	SDL_Point projectPoint(const float& x, const float& y) const;
	//get a point in the world from a point on screen
	SDL_Point inverseProjectPoint(SDL_Point point) const;

	//change camera's zoom, and position based on that
	void changeZoom(const float& amount);

	//check if a point would be visible on screen
	bool visible(const SDL_Point& point) const;
};