#include "editor.h"
#include <fstream>
#include <iostream>

Editor::Editor(b2Body* Terrain)
{
	terrain = Terrain;
	defined = false;
	button = { 100,100,200,100 };
}

bool Editor::Edit(Physics& physics, Graphics& graphics, Input& input)
{
	graphics.camera.freeCam();
	if (button.update(input))
		return true;
	const b2Vec2 position = graphics.camera.inverseProjectPoint(Input::getPos());
	if (input.leftClick2 && !defined)
	{
		defined = true;
		point = position;
	}
	else if (input.leftClick2 && defined)
	{
		physics.addFixtureToBody(terrain, { {point.x * graphics.camera.scaling, point.y * graphics.camera.scaling}, {position.x * graphics.camera.scaling, position.y * graphics.camera.scaling} });
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
	{
		const auto projected = graphics.camera.projectPoint(point.x, point.y);
		graphics.drawLine(projected.x, projected.y, pos.x, pos.y);
	}
	button.draw(graphics);
}

void Editor::importFromFile(Graphics& graphics, Physics& physics, const std::string& path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line;
		std::vector<float> values;
		while (std::getline(file, line))
		{
			if (!line.empty())
				values.push_back(std::stof(line));
		}
		for (auto i = 0; i < std::size(values) / 4; i++)
		{
			physics.addFixtureToBody(terrain, { {values[i * 4] * graphics.camera.scaling, values[i * 4 + 1] * graphics.camera.scaling},{values[i * 4 + 2] * graphics.camera.scaling, values[i * 4 + 3] * graphics.camera.scaling} });
		}
	}
	else std::cout << "Couldn't open target import file" << std::endl;
}

void Editor::exportToFile(const std::string& path) const
{
	std::ofstream file(path);
	for (auto* f = terrain->GetFixtureList(); f; f = f->GetNext())
	{
		if (f->GetShape()->GetType() == b2Shape::e_edge)
		{
			const auto shape = (b2EdgeShape*)f->GetShape();
			file << shape->m_vertex1.x << std::endl << shape->m_vertex1.y << std::endl << shape->m_vertex2.x << std::endl << shape->m_vertex2.y << std::endl << std::endl;
		}
	}
}
