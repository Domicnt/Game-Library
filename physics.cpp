#include "physics.h"

Physics::Physics(const float& x, const float& y, Camera* Camera)
{
	timeStep = 1.0f / 30.0f;
	velocityIterations = 8;
	positionIterations = 3;

	world = new b2World(b2Vec2(x, y));

	camera = Camera;
}

b2Body* Physics::createBody(const bool& dynamic, const b2Vec2& pos)
{
	//create bodyDef
	b2BodyDef bodyDef;
	if (dynamic) bodyDef.type = b2_dynamicBody;
	else bodyDef.type = b2_staticBody;
	//set position
	const SDL_FPoint newPos = camera->inverseProjectPoint({pos.x, pos.y});
	bodyDef.position.Set(newPos.x, newPos.y);
	//create body
	auto* body = world->CreateBody(&bodyDef);
	return body;
}

void Physics::addFixtureToBody(b2Body* body, std::vector<b2Vec2> vertices) const
{
	//create fixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;
	
	//scale vertices
	for (auto& i : vertices)
	{
		camera->inverseProjectPoint({ int(i.x), int(i.y) });
	}
	
	//line
	if (std::size(vertices) == 2)
	{
		b2EdgeShape shape;
		shape.m_vertex1 = vertices[0];
		shape.m_vertex2 = vertices[1];
		fixtureDef.shape = &shape;

		body->CreateFixture(&fixtureDef);
	}
	//polygon
	else if (std::size(vertices) >= 3) {
		b2PolygonShape shape;
		shape.Set(&vertices[0], std::size(vertices));
		fixtureDef.shape = &shape;

		body->CreateFixture(&fixtureDef);
	}
}

void Physics::step()
{
	world->Step(timeStep, velocityIterations, positionIterations);
}