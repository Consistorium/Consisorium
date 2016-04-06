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
		body->CreateFixture(&fixtureDef);

		float halfHeight = (height - width) / 2;
		const int DIVISIONS = b2_maxPolygonVertices;
		const float RADIUS = width / 2;

		b2Vec2 vertices[DIVISIONS];
		b2PolygonShape circleShape;
		b2FixtureDef bottomCircleDef;

		//BOTTOM CIRCLE
		for (int div = 1; div <= DIVISIONS; div++)
		{
			float32 angle = b2_pi + (b2_pi / div);
			float32 xPos, yPos;

			xPos = RADIUS * cosf(angle);
			yPos = -halfHeight + RADIUS * sinf(angle);
			vertices[div - 1] = b2Vec2(xPos, yPos);
		}

		circleShape.Set(vertices, DIVISIONS);
		bottomCircleDef.shape = &circleShape;
		body->CreateFixture(&bottomCircleDef);

		//TOP CIRCLE
		b2FixtureDef topCircleDef;
		for (int div = 1; div <= DIVISIONS; div++)
		{
			float32 angle = b2_pi / div;
			float32 xPos, yPos;

			xPos = RADIUS * cosf(angle);
			yPos = -halfHeight + RADIUS * sinf(angle);
			vertices[div - 1] = b2Vec2(xPos, yPos);
		}

		circleShape.Set(vertices, DIVISIONS);
		topCircleDef.shape = &circleShape;
		body->CreateFixture(&topCircleDef);

		return body;
	}
}