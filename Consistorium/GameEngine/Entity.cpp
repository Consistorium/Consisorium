#include "Entity.h"

namespace Entities
{
	b2Vec2 Entity::getPosition() { return position_; }
	
	int Entity::IdGen = 0;

	int Entity::getId() { return ++IdGen; }

	Entity* Entity::setPosition(b2Vec2 value) 
	{
		position_ = value;
		return this;
	};

	int Entity::getType() { return type_; }

	void Entity::setXDirection(int direction) { xDirection_ = direction; }

	int Entity::getXDirection() { return xDirection_; }

	Entity* Entity::setType(int type)
	{
		type_ = type;
		return this;
	}
}