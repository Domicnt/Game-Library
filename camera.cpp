#include "camera.h"
#include "functions.h"

Camera::Camera(const int& W, const int& H, const float& Scaling)
{
	w = W;
	h = H;
	scaling = Scaling;
	zoom = 1;
	pos = { 0, 0 };
}

SDL_Point Camera::projectPoint(const float& x, const float& y) const
{
	return { int(x * (scaling * zoom) - pos.x), int(y * (scaling * zoom) - pos.y) };
}

SDL_Point Camera::inverseProjectPoint(SDL_Point point) const
{
	return { int((point.x + pos.x) / zoom), int((point.y + pos.y) / zoom) };
}

void Camera::changeZoom(const float& amount)
{
	pos.x += w / 2 * amount;
	pos.y += h / 2 * amount;
	zoom += amount;
}

bool Camera::visible(const SDL_Point& point) const
{
	return point.x >= 0 && point.x <= w && point.y >= 0 && point.y <= h;
}

bool Camera::preScaledVisible(const SDL_FPoint& point) const
{
	return point.x >= 0 && point.x <= w / (scaling * zoom) && point.y >= 0 && point.y <= h / (scaling * zoom);
}