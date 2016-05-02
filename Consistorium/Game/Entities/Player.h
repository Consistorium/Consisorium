#pragma once

#include <SDL\SDL.h>
#include <AnimationManager.h>
#include <GameEngine\FluentEntity.h>

namespace Entities
{
	class Player : public FluentEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 3;
	public:
		Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac);

		~Player();

		void init(SDL_Renderer *renderer);

		void dig();
	};
}