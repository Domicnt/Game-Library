#pragma once

#include "physics.h"

class Functions
{
public:
	//distance between two points
	static float distToPoint(const b2Vec2& a, const b2Vec2& b);
	//vector from point a to point b
	static b2Vec2 vecToPoint(const b2Vec2& a, const b2Vec2& b);
	//angle from point a to point b
	static float angleToPoint(const b2Vec2& a, const b2Vec2& b);

	//collision functions
	//rectangle to rectange collision
	static bool rectVsRect(const float& x1, const float& y1, const float& w1, const float& h1, const float& x2, const float& y2, const float& w2, const float& h2);
};