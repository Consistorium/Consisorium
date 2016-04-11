#include "Skeleton.h"

namespace Entities
{
	Skeleton::Skeleton(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower)
		: DynamicEntity(rc, ac, 0.2f, 10.0f) // doesnt work with constants wtf
	{
	}

	void Skeleton::die()
	{
	}

	Skeleton::~Skeleton()
	{
	}
}