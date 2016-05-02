#pragma once

#include <SDL\SDL.h>
#include <AnimationManager.h>
#include "Enemy.h"

namespace Entities
{
	class Skeleton : public Enemy
	{
	private:
		const float ENTITY_MAX_SPEED = 1;
		
	public:
		Skeleton(
			b2Body* body,
			GameEngine::RenderComponent* rc, 
			GameEngine::AnimationComponent* ac);

		~Skeleton();

		void init(SDL_Renderer *renderer);

		void die();
	};
}