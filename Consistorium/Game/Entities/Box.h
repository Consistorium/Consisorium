#pragma once

#include <Box2D\Box2D.h>

namespace Bodies
{
	class Box
	{
	private:
	public:
		static b2Body* create(b2World* world, b2Vec2 position, float width, float height);
	};
}