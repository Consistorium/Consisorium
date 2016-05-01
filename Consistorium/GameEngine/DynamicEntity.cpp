#include "DynamicEntity.h"

namespace Entities
{
	DynamicEntity::DynamicEntity(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac, float jumpPower, float maxSpeed)
		: GameEntity(body, rc),
		animationComponent_(ac),
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
		b2Vec2 oldVelocity = body_->GetLinearVelocity();
		float jumpForce = body_->GetMass() * getJumpPower() * (-gravity.y);
		b2Vec2 impulse(0, jumpForce);
		body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
	}

	GameEngine::IAnimateable* DynamicEntity::getAnimateableComponent()
	{
		return animationComponent_;
	}
}