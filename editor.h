#pragma once
#include "physics.h"
#include "graphics.h"
#include "input.h"
#include "button.h"

#include <string>

//terrain / level editor
class Editor
{
public:
	//static terrain in the world
	b2Body* terrain;

	//point last clicked
	b2Vec2 point;
	//if point is defined
	bool defined;
	
	//button to export to a file
	Button button;

	//constructor
	Editor(b2Body* Terrain);

	//terrain editor function, returns true if finished editing
	bool Edit(Physics& physics, Graphics& graphics, Input& input);
	//draw things
	void draw(Graphics& graphics, Input& input) const;
	
	//import from a file
	void importFromFile(std::string path);
	//create and export to a file
	void exportToFile(std::string path);
};