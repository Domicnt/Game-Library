#include "game.h"

#include "clock.h"

Game::Game(Physics& physics)
{
	basicGraphics = true;
	lastUpdate = Clock::checkTime();
	updatesPerSecond = 60;
	//creating a static terrain object
	terrain = physics.createBody(false, { 0,0 });
	//camera
	camera = physics.camera;
}

void Game::basicDrawBody(b2Body* body, Graphics& graphics)
{
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
			for (const auto i : shape->m_vertices)
				if (i.x > -INT16_MAX)
					v++;
			SDL_Point last;
			for (auto j = 0; j < v; j++)
			{
				const SDL_Point p1 = j == 0 ? graphics.camera.projectPoint(cos(angle) * shape->m_vertices[j].x - sin(angle) * shape->m_vertices[j].y + pos.x, sin(angle) * shape->m_vertices[j].x + cos(angle) * shape->m_vertices[j].y + pos.y) : last;
				const SDL_Point p2 = graphics.camera.projectPoint(cos(angle) * shape->m_vertices[(j + 1) % v].x - sin(angle) * shape->m_vertices[(j + 1) % v].y + pos.x, sin(angle) * shape->m_vertices[(j + 1) % v].x + cos(angle) * shape->m_vertices[(j + 1) % v].y + pos.y);
				last = p2;
				SDL_RenderDrawLine(graphics.renderer, p1.x, p1.y, p2.x, p2.y);
			}
			break;
		}
		//fixture is an edge shape / line
		case b2Shape::e_edge:
		{
			const auto shape = (b2EdgeShape*)f->GetShape();
			const auto p1 = graphics.camera.projectPoint(cos(angle) * shape->m_vertex1.x - sin(angle) * shape->m_vertex1.y + pos.x, sin(angle) * shape->m_vertex1.x + cos(angle) * shape->m_vertex1.y + pos.y);
			const auto p2 = graphics.camera.projectPoint(cos(angle) * shape->m_vertex2.x - sin(angle) * shape->m_vertex2.y + pos.x, sin(angle) * shape->m_vertex2.x + cos(angle) * shape->m_vertex2.y + pos.y);
			SDL_RenderDrawLine(graphics.renderer, p1.x, p1.y, p2.x, p2.y);
			break;
		}
		//fixture is a circle
		case b2Shape::e_circle:
		{
			const auto shape = (b2CircleShape*)f->GetShape();
			const auto p = graphics.camera.projectPoint(cos(angle) * shape->m_p.x - sin(angle) * shape->m_p.y + pos.x, sin(angle) * shape->m_p.x + cos(angle) * shape->m_p.y + pos.y);
			graphics.drawCircle(p.x,p.y,shape->m_radius * graphics.camera.scaling * graphics.camera.zoom);
		}
		}
	}
}

void Game::basicDraw(Physics& physics, Graphics& graphics)
{
	for (auto* body = physics.world->GetBodyList(); body != nullptr; body = body->GetNext()) {
		if (!graphics.camera.b2BodyVisible(body))
			continue;
		basicDrawBody(body, graphics);
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
	//perform one physics step if it is time to do so
	if (updateTime()) {
		lastUpdate = Clock::checkTime();
		physics.step();
	}
}
