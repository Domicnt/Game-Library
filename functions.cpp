#include "functions.h"

float Functions::distToPoint(const b2Vec2& a, const b2Vec2& b)
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

b2Vec2 Functions::vecToPoint(const b2Vec2& a, const b2Vec2& b)
{
	return { b.x - a.x,b.y - a.y };
}

float Functions::angleToPoint(const b2Vec2& a, const b2Vec2& b)
{
	return atan2f(b.y - a.y, b.x - a.x);
}
