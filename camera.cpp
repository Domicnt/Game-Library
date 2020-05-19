#include "camera.h"
#include "input.h"
#include "functions.h"

Camera::Camera(const int& W, const int& H, const float& Scaling)
{
	w = W;
	h = H;
	scaling = Scaling;
	sw = w / scaling;
	sh = h / scaling;
	zoom = 1;
	pos = { 0, 0 };
}

SDL_Point Camera::projectPoint(const float& x, const float& y) const
{
	return { int(x * (scaling * zoom) - pos.x), int(y * (scaling * zoom) - pos.y) };
}

b2Vec2 Camera::inverseProjectPoint(SDL_Point point) const
{
	return { (point.x + pos.x) / (scaling * zoom), (point.y + pos.y) / (scaling * zoom) };
}

void Camera::changeZoom(const float& amount)
{
	pos.x += w / 2 * amount;
	pos.y += h / 2 * amount;
	zoom += amount;
}

void Camera::freeCam()
{
	if (Input::checkKey('-'))
		changeZoom(-.01f * zoom);
	if (Input::checkKey('='))
		changeZoom(.01f * zoom);
	if (Input::checkKey('w'))
		pos.y -= 1;
	if (Input::checkKey('a'))
		pos.x -= 1;
	if (Input::checkKey('s'))
		pos.y += 1;
	if (Input::checkKey('d'))
		pos.x += 1;
}

bool Camera::visible(SDL_Point point) const
{
	return point.x >= 0 && point.x <= w && point.y >= 0 && point.y <= h;
}

bool Camera::b2BodyVisible(b2Body* body) const
{
	//find aabb
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
	}
	const auto extents = aabb.GetExtents();
	const auto center = aabb.GetCenter();
	//check collision with frame
	return Functions::rectVsRect(center.x - extents.x, center.y - extents.y, extents.x * 2, extents.y * 2, pos.x / scaling / zoom, pos.y / scaling / zoom, sw / zoom, sh / zoom);
}

bool Camera::pointInB2Body(b2Vec2 point, b2Body* body) const
{
	//find aabb
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
	}
	const auto extents = aabb.GetExtents();
	const auto center = aabb.GetCenter();
	//check collision with point
	return Functions::rectVsRect(center.x - extents.x, center.y - extents.y, extents.x * 2, extents.y * 2, point.x, point.y, 0, 0);

}
