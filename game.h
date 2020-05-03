#pragma once

#include "graphics.h"
#include "physics.h"

#include "object.h"

#include <vector>

class Game
{
public:
	//if a basic outline for all physics bodies should be drawn
	bool ifBasicGraphics;

	//last time a physics step was taken
	long float lastUpdate;
	//physics updates per second
	float updatesPerSecond;

	//defines static terrain, add a fixture to add a feature
	b2Body* terrain;

	//vector of objects
	std::vector<Object> objects;

	//constructor
	Game(b2World* world);

	//update objects and make a physics step
	void update(Physics& Box2DWrapper, Graphics& SDLWrapper);
};