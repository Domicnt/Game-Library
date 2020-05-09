#include "physics.h"

Physics::Physics(const float& x, const float& y, Camera* Camera)
{
	timeStep = 1.0f / 30.0f;
	velocityIterations = 8;
	positionIterations = 3;

	world = new b2World(b2Vec2(x, y));

	camera = Camera;
}

b2Body* Physics::createBody(const int& dynamic, const b2Vec2& pos)
{
	//create bodyDef
	b2BodyDef bodyDef;
	if (dynamic == 2) 
		bodyDef.type = b2_kinematicBody;
	else if (dynamic) 
		bodyDef.type = b2_dynamicBody;
	else 
		bodyDef.type = b2_staticBody;
	//set position
	const b2Vec2 newPos = { pos.x / camera->scaling, pos.y / camera->scaling};
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
		i.x /= camera->scaling;
		i.y /= camera->scaling;
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

void Physics::addCircularFixtureToBody(b2Body* body, float radius, b2Vec2 pos) const
{
	//create fixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;

	//scale vertices
	pos.x /= camera->scaling;
	pos.y /= camera->scaling;
	radius /= camera->scaling;

	b2CircleShape shape;
	shape.m_p = pos;
	shape.m_radius = radius;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);
}

b2Joint* Physics::createJoint(b2Body* body1, b2Body* body2, const b2Vec2& localAnchorA, const b2Vec2& localAnchorB) const
{
	//set up the definition for a xxx joint
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body1;
	jointDef.bodyB = body2;
	jointDef.localAnchorA = localAnchorA;
	jointDef.localAnchorB = localAnchorB;
	jointDef.collideConnected = false;

	//create the joint and return it
	return (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

void Physics::step()
{
	world->Step(timeStep, velocityIterations, positionIterations);
}