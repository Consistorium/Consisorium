#pragma once

#include <Box2D\Box2D.h>

namespace Entities
{
	class Entity
	{
	private:
		b2Vec2 position_;
		int type_;
	public:
		virtual b2Vec2 getPosition();

		virtual Entity* setPosition(b2Vec2 value);

		virtual int getType();

		virtual Entity* setType(int type);
	};
}