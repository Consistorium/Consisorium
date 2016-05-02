#include "Skeleton.h"

namespace Entities
{
	Skeleton::Skeleton(
		b2Body* body,
		GameEngine::RenderComponent* rc, 
		GameEngine::AnimationComponent* ac)
		: Enemy(body, rc, ac)
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