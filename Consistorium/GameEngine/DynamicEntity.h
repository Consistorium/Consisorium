#pragma once

#include "GameEntity.h"

#include "AnimationComponent.h"
#include "AnimationManager.h"

namespace Entities
{
	class DynamicEntity : public GameEntity
	{
	protected:
		float jumpPower_;
		float maxSpeed_;
		float scanRange_;
		float range_;
		float damage_;
		float haste_;
		GameEngine::AnimationComponent* animationComponent_;
		GameEngine::AnimationManager animationManager_;
	public:
		DynamicEntity(b2Body*, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac);

		virtual float getJumpPower();

		virtual float getAccelerationImpulse();

		virtual void update();

		virtual void move();

		virtual void jump(b2Vec2 gravity);

		GameEngine::IAnimateable* getAnimateableComponent();

		virtual ~DynamicEntity();
	};
}
