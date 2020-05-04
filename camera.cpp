#include "camera.h"

SDL_Point Camera::projectPoint(SDL_Point point) const
{
	point.x = w / 2 + (point.x - w / 2) * zoom - pos.x;
	point.y = h / 2 + (point.y - h / 2) * zoom - pos.y;
	return point;
}

SDL_Point Camera::inverseProjectPoint(SDL_Point point) const
{
	point.x = w / 2 + (point.x - w / 2) / zoom - pos.x;
	point.y = h / 2 + (point.y - h / 2) / zoom - pos.y;
	return point;
}

void Camera::changeZoom(const float& Zoom)
{
	auto change = Zoom / zoom;
	SDL_Point center = {pos.x + w * zoom, pos.y + h * zoom};
	pos = { int(center.x - w * Zoom), int(center.y - h * Zoom) };
	zoom = Zoom;
}

bool Camera::visible(const SDL_Point& point) const
{
	return point.x >= 0 && point.x <= w && point.y >= 0 && point.y <= h;
}