#include "camera.h"

SDL_FPoint Camera::projectPoint(SDL_FPoint point) const
{
	point.x = w / 2 + (point.x - w / 2) * zoom - pos.x;
	point.y = h / 2 + (point.y - h / 2) * zoom - pos.y;
	return point;
}

SDL_FPoint Camera::inverseProjectPoint(SDL_FPoint point) const
{
	point.x = w / 2 + (point.x - w / 2) / zoom - pos.x;
	point.y = h / 2 + (point.y - h / 2) / zoom - pos.y;
	return point;
}

bool Camera::visible(const SDL_FPoint& point) const
{
	return point.x > 0 && point.x < w && point.y > 0 && point.y < h;
}