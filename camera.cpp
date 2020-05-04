#include "camera.h"

SDL_Point Camera::projectPoint(const SDL_Point& point) const
{
	return SDL_Point();
}

SDL_Point Camera::inverseProjectPoint(const SDL_Point& point) const
{
	return SDL_Point();
}

bool Camera::visible(const SDL_Point& point) const
{
	return false;
}
