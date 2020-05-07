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

bool Functions::rectVsRect(const float& x1, const float& y1, const float& w1, const float& h1, const float& x2, const float& y2, const float& w2, const float& h2)
{
	return x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2;
}
