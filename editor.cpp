#include "editor.h"
#include <fstream>

Editor::Editor(b2Body* Terrain)
{
	terrain = Terrain;
	defined = false;
	button = {100,100,200,100};
}

bool Editor::Edit(Physics& physics, Graphics& graphics, Input& input)
{
	graphics.camera.freeCam();
	if (button.update(input))
		return true;
	const auto pos = Input::getPos();
	const b2Vec2 position = { float(pos.x), float(pos.y) };
	if(input.leftClick2 && !defined)
	{
		defined = true;
		point = position;
	} else if (input.leftClick2 && defined)
	{
		physics.addFixtureToBody(terrain, {point, position});
		if (input.rightButton)
			point = position;
		else
			defined = false;
	}
	return false;
}

void Editor::draw(Graphics& graphics, Input& input) const
{
	const auto pos = Input::getPos();
	if (defined)
		graphics.drawLine(point.x, point.y, pos.x, pos.y);
	button.draw(graphics);
}

void Editor::importFromFile(std::string path)
{
}

void Editor::exportToFile(std::string path)
{
}
