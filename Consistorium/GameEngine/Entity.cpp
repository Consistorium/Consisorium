#include "Entity.h"

namespace Entities
{
	b2Vec2 Entity::getPosition() { return position_; }
	
	Entity* Entity::setPosition(b2Vec2 value) 
	{
		position_ = value;
		return this;
	};

	int Entity::getType()
	{
		return type_;
	}

	Entity* Entity::setType(int type)
	{
		type_ = type;
		return this;
	}
}