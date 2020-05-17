#pragma once

#include "vcpkg/installed/x86-windows/include/SDL2/SDL.h"
#include "vcpkg/installed/x86-windows/include/box2d/box2d.h"

class Camera
{
public:
	//position
	SDL_FPoint pos;
	//size of the window being rendered to
	int w, h;
	
	//scaling for physics objects
	float scaling;
	//width and height of the camera in relation to the box2d world
	float sw, sh;
	
	//magnification for everything
	float zoom;

	//constructor
	Camera() = default;
	Camera(const int& W, const int& H, const float& Scaling);
	
	//get a point on screen from a point in the world
	SDL_Point projectPoint(const float& x, const float& y) const;
	//get a point in the world from a point on screen
	b2Vec2 inverseProjectPoint(SDL_Point point) const;

	//change camera's zoom, and position based on that
	void changeZoom(const float& amount);

	//check if a point would be visible on screen
	bool visible(SDL_Point point) const;
	//check if a box2d body, scaled up, might be visible on screen
	bool b2BodyVisible(b2Body* body) const;
	//check if a point would be inside a b2Body
	bool pointInB2Body(b2Vec2 point, b2Body* body) const;

};