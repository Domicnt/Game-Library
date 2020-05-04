#include "game.h"

#include "clock.h"

Game::Game(b2World* world)
{
	basicGraphics = true;
	lastUpdate = Clock::checkTime();
	updatesPerSecond = 60;
	//creating a static terrain object
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0, 0);
	terrain = world->CreateBody(&bodyDef);
}

void Game::basicDraw(Physics& physics, Graphics& graphics)
{
	auto* body = physics.world->GetBodyList();
	auto loop = true;
	while (loop) {
		//get position and angle of body
		auto const pos = body->GetPosition();
		auto const angle = body->GetAngle();
		//loop through every fixture in the body
		for (auto* f = body->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetShape()->GetType()) {
			default:
				break;
			//fixture is a polygon
			case b2Shape::e_polygon:
			{
				auto shape = (b2PolygonShape*)f->GetShape();
				auto v = 0;
				//check if any vertices are undefined
				for (auto i : shape->m_vertices)
				{
					if (i.x > -1000000)
					{
						v++;
					}
				}
				for (auto j = 0; j < v; j++)
				{
					const SDL_Point p1 = graphics.camera.projectPoint({ int(cos(angle) * shape->m_vertices[j].x - sin(angle) * shape->m_vertices[j].y + pos.x), int(sin(angle) * shape->m_vertices[j].x + cos(angle) * shape->m_vertices[j].y + pos.y) });
					const SDL_Point p2 = graphics.camera.projectPoint({ int(cos(angle) * shape->m_vertices[(j + 1) % v].x - sin(angle) * shape->m_vertices[(j + 1) % v].y + pos.x), int(sin(angle) * shape->m_vertices[(j + 1) % v].x + cos(angle) * shape->m_vertices[(j + 1) % v].y + pos.y) });
					graphics.drawLine(p1.x, p1.y, p2.x, p2.y);
				}
				break;
			}
			//fixture is an edge shape / line
			case b2Shape::e_edge:
			{
				const auto shape = (b2EdgeShape*)f->GetShape();
				const SDL_Point p1 = graphics.camera.projectPoint({ int(cos(angle) * shape->m_vertex1.x - sin(angle) * shape->m_vertex1.y + pos.x), int(sin(angle) * shape->m_vertex1.x + cos(angle) * shape->m_vertex1.y + pos.y) });
				const SDL_Point p2 = graphics.camera.projectPoint({ int(cos(angle) * shape->m_vertex2.x - sin(angle) * shape->m_vertex2.y + pos.x), int(sin(angle) * shape->m_vertex2.x + cos(angle) * shape->m_vertex2.y + pos.y) });
				graphics.drawLine(p1.x, p1.y, p2.x, p2.y);
				break;
			}
			}
			//go to next body, if there is one - otherwise, exit
			if (body->GetNext() != nullptr)
			{
				body = body->GetNext();
			}
			else
			{
				loop = false;
			}
		}
	}
}

void Game::update(Physics& physics, Graphics& graphics)
{
	//basic outline
	if (basicGraphics)
		basicDraw(physics, graphics);
	//draw all objects
	for (auto& i : objects)
		i.draw(graphics);
	//perform one physics step if it time to do so
	if (lastUpdate + 1000 / updatesPerSecond <= Clock::checkTime()) {
		lastUpdate += 1000 / updatesPerSecond;
		physics.step();
	}
}
