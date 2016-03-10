#include "Entity.h"

Entity::Entity(bool anchorState)
	: anchorState_(anchorState)
{
}

Entity::~Entity()
{
}

bool Entity::isAnchored()
{
	return anchorState_;
}

void Entity::toggleAnchored()
{
	anchorState_ = anchorState_ ? false : true;
}