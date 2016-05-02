#include "FluentEntity.h"

namespace Entities
{
	FluentEntity::FluentEntity(b2Body* body,
		GameEngine::RenderComponent* rc,
		GameEngine::AnimationComponent* ac)
		: DynamicEntity(body, rc, ac)
	{

	}

	FluentEntity* FluentEntity::setJumpPower(float value)
	{
		jumpPower_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setScanRange(float value)
	{
		scanRange_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setDamage(float value)
	{
		damage_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setRange(float value)
	{
		range_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setHaste(float value)
	{
		haste_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setMaxSpeed(float value)
	{
		maxSpeed_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setHealth(float value)
	{
		health_ = value;
		return this;
	}

	FluentEntity* FluentEntity::setMaxHealth(float value)
	{
		maxHealth_ = value;
		return this;
	}

	FluentEntity::~FluentEntity()
	{
	}
}