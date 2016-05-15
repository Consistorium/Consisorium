#pragma once

#include <vector>
#include <memory>
#include <SDL\SDL.h>
#include <AnimationManager.h>
#include <GameEngine\FluentEntity.h>
#include <GameEngine\EventManager.h>
#include "../Utils/ItemSlot.h"

namespace Entities
{
	class Player : public FluentEntity
	{
	private:
		const float PLAYER_MAX_SPEED = 3;	
		std::vector<std::shared_ptr<Utils::ItemSlot>> actionbar_;
		std::vector<std::shared_ptr<Utils::ItemSlot>> inventory_;
		int actionbarSelected_;
		int footContacts_;
		int leftSensorContacts_;
		int rightSensorContacts_;
	public:
		const float ACTIONBAR_SIZE = 8;
		const float INVENTORY_SIZE = 18;

		Player(b2Body*, GameEngine::RenderComponent*, GameEngine::AnimationComponent*, EventManager&);

		~Player();

		void init(SDL_Renderer *renderer);

		void dig();

		int addToActionbar(Entities::GameEntity*);

		int addToInventory(Entities::GameEntity*);

		bool rightSensorSensing();

		bool leftSensorSensing();

		bool canJump();

		std::vector<std::shared_ptr<Utils::ItemSlot>> getInventory();

		std::vector<std::shared_ptr<Utils::ItemSlot>> getActionbar();
	};
}