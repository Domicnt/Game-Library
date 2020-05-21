#pragma once
#include "physics.h"
#include "graphics.h"
#include "input.h"
#include "menu.h"

#include <string>

//terrain / level editor
class Editor
{
public:
	//point last clicked
	b2Vec2 point;
	//if point is defined
	bool defined;

	//points last clicked
	std::vector<b2Vec2> points;
	//if points are defined
	bool pointsDefined;

	//current tool
	int tool;
	enum tool {line, rectangle, circle, polygon};
	
	//menu for editor controls
	Menu menu;

	//constructor
	Editor();

	//edit a body, returns true if finished
	bool editBody(Physics& physics, Graphics& graphics, Input& input, b2Body* body);
	//draw things
	void draw(Graphics& graphics, Input& input) const;
	
	//import from a file
	static void importFromFile(Graphics& graphics, Physics& physics, const std::string& path, b2Body* body);
	//export to a file, create it if it doesn't already exist
	static void exportToFile(const std::string& path, b2Body* body);
};