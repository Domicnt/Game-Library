#pragma once
#include "vcpkg/installed/x86-windows/include/box2d/box2d.h"

#include "camera.h"

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

	//For creating objects in the right place
	Camera* camera;

	//constructor, takes x and y components of gravity, and camera
	Physics(const float& x, const float& y, Camera* Camera);

	//create a physics body
	b2Body* createBody(const int& dynamic, const b2Vec2& pos);
	//add a fixture to a body, takes relative position of vertices, which must be in counter-clockwise order and cannot be concave
	void addFixtureToBody(b2Body* body, std::vector<b2Vec2> vertices) const;
	//add a fixture to a body, takes radius and relative position
	void addCircularFixtureToBody(b2Body* body, float radius, b2Vec2 pos) const;

	//create a revolute joint between two bodies
	b2Joint* createJoint(b2Body* body1, b2Body* body2);
	
	//perform one physics step
	void step();
};