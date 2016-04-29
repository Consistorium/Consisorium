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

		float halfHeight = (height - width) / 2;
		const int DIVISIONS = b2_maxPolygonVertices;
		const float RADIUS = width / 2;

		b2Vec2 vertices[DIVISIONS];
		b2PolygonShape circleShape;

		//BOTTOM CIRCLE
		for (int i = 1; i <= 4; i++)
		{	
			b2FixtureDef bottomCircleDef;
			bottomCircleDef.density = 1;
			float endAngle = b2_pi / 4 * i;

			for (int div = 1; div <= DIVISIONS; div++)
			{
				float32 angle = b2_pi + (endAngle / div);
				float32 xPos, yPos;

				xPos = RADIUS * cosf(angle);
				yPos = -halfHeight + RADIUS * sinf(angle);
				vertices[div - 1] = b2Vec2(xPos, yPos);
			}

			circleShape.Set(vertices, DIVISIONS);
			bottomCircleDef.shape = &circleShape;
			body->CreateFixture(&bottomCircleDef);
		}

		//TOP CIRCLE
		b2FixtureDef topCircleDef;
		topCircleDef.density = 1;
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