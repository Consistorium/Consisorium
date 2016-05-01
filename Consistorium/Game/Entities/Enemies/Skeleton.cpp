#include "Skeleton.h"

namespace Entities
{
	Skeleton::Skeleton(
		b2Body* body,
		GameEngine::RenderComponent* rc, 
		GameEngine::AnimationComponent* ac, 
		float jumpPower, 
		float scanRange, 
		float damage, 
		float range,
		float haste)
		: Enemy(body, rc, ac, 0.2f, scanRange, damage, range, haste)
	{
		animationManager_.setAnimation("Appear", false);
		setHealth(70);
	}

	void Skeleton::die()
	{
	}

	Skeleton::~Skeleton()
	{
	}
}