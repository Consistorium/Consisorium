#pragma once

#include <SDL\SDL.h>
#include <AnimationManager.h>
#include "DynamicEntity.h"

namespace Entities
{
	class Player : public DynamicEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 0.3;
	public:
		//TODO:apply builder pattern
		Player(std::string defaultAnimation, float width, float height, float jumpPower);
		~Player();

		void init(SDL_Renderer *renderer);

		void die();

		std::string getAnimationsFolder() override;

		b2Vec2 getScale() override;
	};
}