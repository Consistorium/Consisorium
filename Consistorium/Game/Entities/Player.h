#pragma once

#include <SDL\SDL.h>
#include <AnimationManager.h>
#include "DynamicEntity.h"

namespace Entities
{
	class Player : public DynamicEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 3;
	public:
		//TODO:apply builder pattern
		Player(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower);

		~Player();

		void init(SDL_Renderer *renderer);

		void die();
	};
}