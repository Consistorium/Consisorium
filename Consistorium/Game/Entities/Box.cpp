#include "Box.h"

#include <Game\Globals\Constants.h>

namespace Bodies
{
	b2Body* Box::create(b2World* world, b2Vec2 position, float width, float height)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(position.x / Globals::PIXELS_PER_METER, position.y / Globals::PIXELS_PER_METER);
		bodyDef.fixedRotation = true;
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(width / 2.0f, height / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		body->CreateFixture(&fixtureDef);

		return body;
	}
}