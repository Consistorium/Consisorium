#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

#include <SDL\SDL.h>
#include <GameEngine\Entity.h>
#include <Game\Entities\Player.h>
#include <GameEngine\GameEntity.h>
#include <GameEngine\Renderer.h>
#include <GameEngine\RenderComponent.h>
#include "Actionbar.h"
#include "Inventory.h"
#include <Game\Utils\SlotDescriptor.h>
#include <EventManager.h>

namespace UI
{
	class InterfaceManager
	{
	private:
		std::unordered_map<std::string, GameEngine::RenderComponent*> cache_;
		std::shared_ptr<Entities::Player> player_;
		std::shared_ptr<GameEngine::Renderer> renderer_;
		b2Vec2 windowSize_;
		SDL_Window* window_;
		std::unique_ptr<Actionbar> actionbar_;
		std::unique_ptr<Inventory> inventory_;
		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> inventoryPage_;
		void createActionbar();
	public:
		InterfaceManager(GameEngine::Renderer*, SDL_Window*, Entities::Player*, EventManager& eManager);

		void showHud();

		void toggleInventory();

		void showHealth(float maxValue, float value);

		void showActionBar();

		//void update();

		Actionbar* getActionbar();

		Inventory* getInventory();

		void closeInventory();

		~InterfaceManager();
	};
}