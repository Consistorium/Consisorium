#include "DynamicEntity.h"

#include <iostream>

namespace Entities
{
	DynamicEntity::DynamicEntity(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac)
		: GameEntity(body, rc),
		animationComponent_(ac),
		animationManager_(animationComponent_)
	{
		renderComponent_->setStatic(false);
	}

	DynamicEntity::~DynamicEntity()
	{
	}

	void DynamicEntity::update()
	{
		animationManager_.updateAnimation();
	}

	float DynamicEntity::getJumpPower()
	{
		return jumpPower_;
	}

	float DynamicEntity::getAccelerationImpulse()
	{
		float xVelocity = body_->GetLinearVelocity().x;
		return (maxSpeed_ - (xVelocity * getXDirection())) * getXDirection();
	}

	void DynamicEntity::move()
	{
		animationManager_.setAnimation("Walk", false);
		float impulse = getAccelerationImpulse();
		b2Vec2 force(impulse, 0);
		body_->ApplyLinearImpulse(force, body_->GetWorldCenter(), true);
	}

	void DynamicEntity::jump(b2Vec2 gravity)
	{
		
		//float maxJumpForce = body_->GetMass() * getJumpPower() * (-gravity.y) / 1.2; //happy constant
		//animationManager_.setAnimation("Jump", false);
		//float oldVelocity = body_->GetLinearVelocity().y;
		float jumpForce = body_->GetMass() * getJumpPower() * (-gravity.y) / 1.2;
		/*if (oldVelocity > 0)
		{
			jumpForce -= oldVelocity;
		}*/

		b2Vec2 impulse(0, jumpForce);
		body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
	}

	GameEngine::IAnimateable* DynamicEntity::getAnimateableComponent()
	{
		return animationComponent_;
	}
}