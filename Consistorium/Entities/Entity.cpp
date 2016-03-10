#include "Entity.h"

Entity::Entity(bool anchor_state)
	: anchor_state_(anchor_state)
{
}

Entity::~Entity()
{
}

bool Entity::isAnchored()
{
	return anchor_state_;
}

bool Entity::toggleAnchored()
{
	anchor_state_ = anchor_state_ ? false : true;
}