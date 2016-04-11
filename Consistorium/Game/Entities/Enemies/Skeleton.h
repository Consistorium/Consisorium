#pragma once

#include <SDL\SDL.h>
#include <AnimationManager.h>
#include "DynamicEntity.h"

namespace Entities
{
	class Skeleton : public DynamicEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 3;
	public:
		Skeleton(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower);

		~Skeleton();

		void init(SDL_Renderer *renderer);

		void die();
	};
}