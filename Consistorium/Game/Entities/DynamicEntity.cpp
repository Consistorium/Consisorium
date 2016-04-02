#include "DynamicEntity.h"

namespace Entities
{
	DynamicEntity::DynamicEntity(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower, float maxSpeed)
		: GameEntity(rc),
		animationComponent_(ac.getAnimationsFolder(), ac.getDefaultAnimation(), ac.getAnimationSpeed(), renderComponent_.getTextureName()),
		animationManager_(animationComponent_),
		jumpPower_(jumpPower),
		maxSpeed_(maxSpeed),
		xDirection_(0)
	{
	}

	DynamicEntity::~DynamicEntity()
	{
	}

	void DynamicEntity::update()
	{
		animationManager_.updateAnimation();
	}


	void DynamicEntity::setXDirection(int direction)
	{
		xDirection_ = direction;
	}

	void DynamicEntity::setJumpPower(float power)
	{
		jumpPower_ = power;
	}

	float DynamicEntity::getJumpPower()
	{
		return jumpPower_;
	}

	float DynamicEntity::getAccelerationImpulse()
	{
		float xVelocity = body_->GetLinearVelocity().x;

		return (maxSpeed_ - (xVelocity * xDirection_)) * xDirection_;
	}

	GameEngine::IAnimateable* DynamicEntity::getAnimateableComponent()
	{
		return &animationComponent_;
	}
}