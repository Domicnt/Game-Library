#include "editor.h"
#include "functions.h"
#include <fstream>
#include <iostream>

Editor::Editor(Graphics& graphics)
{
	defined = false;
	pointsDefined = false;
	tool = line;
	//exit button
	menu.buttons.emplace_back(50, 10, 100, 50, graphics, "Exit Editor");
	//line tool
	menu.buttons.emplace_back(200, 10, 100, 50, graphics, "Line Tool");
	//rectangle tool
	menu.buttons.emplace_back(350, 10, 100, 50, graphics, "Rectangle Tool");
	//circle tool
	menu.buttons.emplace_back(500, 10, 100, 50, graphics, "Circle Tool");
	//polygon tool
	menu.buttons.emplace_back(650, 10, 100, 50, graphics, "Polygon Tool");
}

bool Editor::editBody(Physics& physics, Graphics& graphics, Input& input, b2Body* body)
{
	switch (menu.update(input, graphics))
	{
	case 1:
		return true;
	case 2:
		tool = line;
		return false;
	case 3:
		tool = rectangle;
		return false;
	case 4:
		tool = circle;
		return false;
	case 5:
		tool = polygon;
		return false;
	default:
		break;
	}
	graphics.camera.freeCam();
	const auto position = graphics.camera.inverseProjectPoint(Input::getPos(graphics.renderer));
	const auto bodyPos = body->GetWorldCenter();
	switch (tool)
	{
	case line:
		if (input.leftClick2 && !defined)
		{
			defined = true;
			point = position;
		}
		else if (input.leftClick2 && defined)
		{
			physics.addFixtureToBody(body, { {(point.x - bodyPos.x) * graphics.camera.scaling, (point.y - bodyPos.y) * graphics.camera.scaling}, {(position.x - bodyPos.x) * graphics.camera.scaling, (position.y - bodyPos.y) * graphics.camera.scaling} });
			if (input.rightButton)
				point = position;
			else
				defined = false;
		}
		break;
	case rectangle:
		if (input.leftClick2 && !defined)
		{
			defined = true;
			point = position;
		}
		else if (input.leftClick2 && defined && position.x != point.x && position.y != point.y)
		{
			physics.addFixtureToBody(body, { {(point.x - bodyPos.x) * graphics.camera.scaling, (point.y - bodyPos.y) * graphics.camera.scaling},{(point.x - bodyPos.x) * graphics.camera.scaling, (position.y - bodyPos.y) * graphics.camera.scaling},{(position.x - bodyPos.x) * graphics.camera.scaling, (position.y - bodyPos.y) * graphics.camera.scaling},{(position.x - bodyPos.x) * graphics.camera.scaling, (point.y - bodyPos.y) * graphics.camera.scaling} });
			defined = false;
		}
		break;
	case circle:
		if (input.leftClick2 && !defined)
		{
			defined = true;
			point = position;
		}
		else if (input.leftClick2 && defined)
		{
			physics.addCircularFixtureToBody(body, Functions::distToPoint(point, position) * graphics.camera.scaling, { (point.x - bodyPos.x) * graphics.camera.scaling, (point.y - bodyPos.y) * graphics.camera.scaling });
			defined = false;
		}
		break;
	case polygon:
		if (input.leftClick2 && !pointsDefined)
		{
			pointsDefined = true;
			points = { {position.x, position.y} };
		}
		else if (input.leftClick2 && pointsDefined)
		{
			for (const auto& i : points)
			{
				if (i == position)
				{
					break;
				}
			}
			if (std::size(points) < 8)
				points.emplace_back(position.x, position.y);
			else
				std::cout << "Maximum of 8 vertices in a polygon" << std::endl;
		}
		else if (input.rightClick2 && pointsDefined)
		{
			auto points2 = points;
			for (auto& i : points2)
			{
				i -= bodyPos;
				i *= graphics.camera.scaling;
			}
			physics.addFixtureToBody(body, points2);
			pointsDefined = false;
		}
		break;
	}
	return false;
}

void Editor::draw(Graphics& graphics, Input& input) const
{
	const auto position = Input::getPos(graphics.renderer);
	switch (tool)
	{
	case line:
		if (defined)
		{
			const auto projected = graphics.camera.projectPoint(point.x, point.y);
			graphics.drawLine(projected.x, projected.y, position.x, position.y);
		}
		break;
	case rectangle:
		if (defined)
		{
			const auto projected = graphics.camera.projectPoint(point.x, point.y);
			graphics.drawRect(projected.x, projected.y, position.x, position.y);
		}
		break;
	case circle:
		if (defined)
		{
			const auto projected = graphics.camera.projectPoint(point.x, point.y);
			graphics.drawCircle(projected.x, projected.y, Functions::distToPoint({ float(projected.x), float(projected.y) }, { float(position.x), float(position.y) }));
		}
		break;
	case polygon:
		if (pointsDefined)
		{
			std::vector<SDL_Point> projecteds = {};
			for (const auto& i : points)
			{
				projecteds.push_back(graphics.camera.projectPoint(i.x, i.y));
			}
			for (auto i = 0; i < std::size(projecteds) - 1; i++)
				graphics.drawLine(projecteds[i].x, projecteds[i].y, projecteds[i + 1].x, projecteds[i + 1].y);
			graphics.drawLine(projecteds[std::size(projecteds) - 1].x, projecteds[std::size(projecteds) - 1].y, position.x, position.y);
			graphics.drawLine(position.x, position.y, projecteds[0].x, projecteds[0].y);
		}
		break;
	}
	menu.draw(graphics);
}

void Editor::importFromFile(Graphics& graphics, Physics& physics, const std::string& path, b2Body* body)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string str;
		std::vector<std::vector<float>> polygons;
		std::vector<std::vector<float>> circles;
		int type = 0;
		//returns false when it reaches the end of the file
		while (std::getline(file, str))
		{
			if (str == "polygon")
			{
				type = polygon;
				polygons.emplace_back();
				continue;
			}
			else if (str == "circle")
			{
				type = circle;
				circles.emplace_back();
				continue;
			}
			if (!str.empty())
			{
				switch (type)
				{
				default:
					break;
				case polygon:
					polygons[std::size(polygons) - 1].push_back(std::stof(str));
					break;
				case circle:
					circles[std::size(circles) - 1].push_back(std::stof(str));
					break;
				}
			}
		}
		for (const auto& i : polygons)
		{
			std::vector<b2Vec2> vertices;
			for (auto j = 0; j < std::size(i); j += 2)
			{
				vertices.emplace_back(i[j] * graphics.camera.scaling, i[j + 1] * graphics.camera.scaling);
			}
			physics.addFixtureToBody(body, vertices);
		}
		for (auto i : circles)
		{
			physics.addCircularFixtureToBody(body, i[0] * graphics.camera.scaling, { i[1] * graphics.camera.scaling, i[2] * graphics.camera.scaling });
		}

	}
	else std::cout << "Couldn't open target import file" << std::endl;
}

void Editor::exportToFile(const std::string& path, b2Body* body)
{
	std::ofstream file(path);
	for (auto* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		switch (f->GetShape()->GetType())
		{
		case b2Shape::e_edge:
		{
			const auto edge = (b2EdgeShape*)f->GetShape();
			//edge is really just a polygon with two vertices
			file << "polygon" << std::endl << edge->m_vertex1.x << std::endl << edge->m_vertex1.y << std::endl << edge->m_vertex2.x << std::endl << edge->m_vertex2.y << std::endl << std::endl;
			break;
		}
		case b2Shape::e_polygon:
		{
			const auto polygon = (b2PolygonShape*)f->GetShape();
			file << "polygon" << std::endl;
			auto v = 0;
			//check if any vertices are undefined
			for (const auto i : polygon->m_vertices)
				if (i.x > -INT16_MAX)
					v++;
			for (auto i = 0; i < v; i++)
			{
				file << polygon->m_vertices[i].x << std::endl << polygon->m_vertices[i].y << std::endl;
			}
			file << std::endl << std::endl;
			break;
		}
		case b2Shape::e_circle:
		{
			const auto circle = (b2CircleShape*)f->GetShape();
			file << "circle" << std::endl << circle->m_p.x << std::endl << circle->m_p.y << std::endl << circle->m_radius << std::endl << std::endl;
			break;
		}
		}
	}
}
