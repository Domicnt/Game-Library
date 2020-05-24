#pragma once

#include "graphics.h"
#include "physics.h"

#include "object.h"

#include <vector>

class Game
{
public:
	//if a basic outline for all physics bodies should be drawn
	bool basicGraphics;

	Camera* camera;

	//last time a physics step was taken
	double lastUpdate;
	//physics updates per second
	float updatesPerSecond;

	//defines static terrain, add a fixture to add a feature
	b2Body* terrain;

	//vector of objects
	std::vector<Object> objects;

	//constructor
	Game(Physics& physics);

	//basic outline for a physics body
	void basicDrawBody(b2Body* body, Graphics& graphics);
	//basic outline for all physics bodies
	void basicDraw(Physics& physics, Graphics& graphics);
	//checks if it is time for an update
	bool updateTime() const;
	//update objects and make a physics step
	void update(Physics& physics, Graphics& graphics);
};