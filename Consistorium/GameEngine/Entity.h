#pragma once

#include <Box2D\Box2D.h>

namespace Entities
{
	class Entity
	{
	protected:
		b2Vec2 position_;
		int xDirection_ = 0;
		int type_;
		int id_;
	public:
		Entity();

		virtual b2Vec2 getPosition();

		virtual Entity* setPosition(b2Vec2 value);

		virtual int getType();

		virtual Entity* setType(int type);

		virtual void setXDirection(int direction);

		virtual int getXDirection();

		int getId();

		//virtual ~Entity();
	};
}