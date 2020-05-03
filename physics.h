#pragma once
#include "vcpkg/installed/x86-windows/include/box2d/box2d.h"

#include <vector>

class Physics
{
public:
	//variables for the b2World
	float timeStep;
	float velocityIterations;
	float positionIterations;

	//holds all physics objects
	b2World* world;

	//constructor, takes x and y components of gravity
	Physics(const float& x, const float& y);

	//create a physics body
	b2Body* createBody(const bool& dynamic, const b2Vec2& pos);
	//add a fixture to a body, takes relative position of vertices, which must be in counter-clockwise order and cannot be concave
	void addFictureToBody(const b2Body* body, const std::vector<b2Vec2>& vertices);

	//perform one physics step
	void step();
};