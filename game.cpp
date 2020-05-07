#include "game.h"

#include "clock.h"

Game::Game(b2World* world, Camera* Camera)
{
	basicGraphics = true;
	lastUpdate = Clock::checkTime();
	updatesPerSecond = 60;
	//creating a static terrain object
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0, 0);
	terrain = world->CreateBody(&bodyDef);
	camera = Camera;
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
					const SDL_FPoint p1 = { cos(angle) * shape->m_vertices[j].x - sin(angle) * shape->m_vertices[j].y + pos.x, sin(angle) * shape->m_vertices[j].x + cos(angle) * shape->m_vertices[j].y + pos.y };
					const SDL_FPoint p2 = { cos(angle) * shape->m_vertices[(j + 1) % v].x - sin(angle) * shape->m_vertices[(j + 1) % v].y + pos.x, sin(angle) * shape->m_vertices[(j + 1) % v].x + cos(angle) * shape->m_vertices[(j + 1) % v].y + pos.y };
					if (!camera->preScaledVisible(p1) && !camera->preScaledVisible(p2))
						continue;
					const auto pp1 = graphics.camera.projectPoint( p1.x, p1.y );
					const auto pp2 = graphics.camera.projectPoint( p2.x, p2.y );
					SDL_RenderDrawLine(graphics.renderer, pp1.x, pp1.y, pp2.x, pp2.y);
				}
				break;
			}
			//fixture is an edge shape / line
			case b2Shape::e_edge:
			{
				const auto shape = (b2EdgeShape*)f->GetShape();
				const SDL_FPoint p1 = { cos(angle) * shape->m_vertex1.x - sin(angle) * shape->m_vertex1.y + pos.x, sin(angle) * shape->m_vertex1.x + cos(angle) * shape->m_vertex1.y + pos.y };
				const SDL_FPoint p2 = { cos(angle) * shape->m_vertex2.x - sin(angle) * shape->m_vertex2.y + pos.x, sin(angle) * shape->m_vertex2.x + cos(angle) * shape->m_vertex2.y + pos.y };
				if (!camera->preScaledVisible(p1) && !camera->preScaledVisible(p2))
					break;
				const auto pp1 = graphics.camera.projectPoint(p1.x, p1.y);
				const auto pp2 = graphics.camera.projectPoint(p2.x, p2.y);
				SDL_RenderDrawLine(graphics.renderer, pp1.x, pp1.y, pp2.x, pp2.y);
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

bool Game::updateTime() const
{
	return lastUpdate + 1000 / updatesPerSecond <= Clock::checkTime();
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
	if (updateTime()) {
		lastUpdate += 1000 / updatesPerSecond;
		physics.step();
	}
}
