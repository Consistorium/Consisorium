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

	void DynamicEntity::move()
	{
		float impulse = getAccelerationImpulse();
		b2Vec2 force(impulse, 0);
		body_->ApplyLinearImpulse(force, body_->GetWorldCenter(), true);
	}

	void DynamicEntity::jump(b2Vec2 gravity)
	{
		float impulse = body_->GetMass() * (-gravity.y) * getJumpPower();
		b2Vec2 force(0, impulse);
		body_->ApplyLinearImpulse(force, body_->GetWorldCenter(), true);
	}

	GameEngine::IAnimateable* DynamicEntity::getAnimateableComponent()
	{
		return &animationComponent_;
	}
}