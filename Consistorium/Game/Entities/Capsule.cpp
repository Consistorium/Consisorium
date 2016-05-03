#include "Capsule.h"

namespace Entities
{
	b2Body* Capsule::create(b2World* world, b2Vec2 position, float width, float height)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.fixedRotation = true;
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(width / 2.0f, (height - width) / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0;
		body->CreateFixture(&fixtureDef);

		// Create the circles
		b2CircleShape circleShape;
		circleShape.m_radius = width / 2.0f;

		b2FixtureDef circleDef;
		circleDef.shape = &circleShape;
		circleDef.density = 1;

		// Bottom circle
		circleShape.m_p.Set(0.0f, (-height + width) / 2.0f);
		body->CreateFixture(&circleDef);

		// Top Circle
		circleShape.m_p.Set(0.0f, (height - width) / 2.0f);
		body->CreateFixture(&circleDef);

		return body;
	}
}