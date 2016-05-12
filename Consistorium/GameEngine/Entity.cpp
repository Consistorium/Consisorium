#include "Entity.h"

namespace Entities
{
	static int IdGen = 0;

	Entity::Entity()
	{
		id_ = ++IdGen;
	}

	int Entity::getId() { return id_; }

	b2Vec2 Entity::getPosition() { return position_; }

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

	/*Entity::~Entity()
	{

	}*/
}