#pragma once

#include <Box2D\Box2D.h>

namespace Entities
{
	class Entity
	{
	private:
		static int IdGen;
		b2Vec2 position_;
	public:
		virtual b2Vec2 getPosition();

		virtual Entity* setPosition(b2Vec2 value);

		int getId();
	};
}