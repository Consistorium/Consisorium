#pragma once

#include "DynamicEntity.h"

namespace Entities
{
	class FluentEntity : public DynamicEntity
	{
	public:
		FluentEntity(b2Body* body,
			GameEngine::RenderComponent* rc,
			GameEngine::AnimationComponent* ac);

		FluentEntity* setJumpPower(float value);

		FluentEntity* setScanRange(float value);

		FluentEntity* setDamage(float value);

		FluentEntity* setRange(float value);

		FluentEntity* setHaste(float value);

		FluentEntity* setMaxSpeed(float value);

		FluentEntity* setHealth(float value);

		FluentEntity* setMaxHealth(float value);

		~FluentEntity();
	};
}