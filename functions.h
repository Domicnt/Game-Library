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
};