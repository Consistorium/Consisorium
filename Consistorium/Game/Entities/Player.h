#pragma once

#include <vector>
#include <memory>
#include <SDL\SDL.h>
#include <AnimationManager.h>
#include <GameEngine\FluentEntity.h>

namespace Entities
{
	class Player : public FluentEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 3;
		std::vector<std::shared_ptr<Entities::GameEntity>> actionbar_;
		std::vector<std::shared_ptr<Entities::GameEntity>> inventory_;
	public:
		const float ACTIONBAR_SIZE = 8;
		const float INVENTORY_SIZE = 16;

		Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac);

		~Player();

		void init(SDL_Renderer *renderer);

		void dig();

		bool addToActionbar(Entities::GameEntity*);

		bool addToInventory(Entities::GameEntity*);

		std::vector<std::shared_ptr<Entities::GameEntity>> getInventory();

		std::vector<std::shared_ptr<Entities::GameEntity>> getActionbar();
	};
}