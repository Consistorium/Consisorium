#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

#include <SDL\SDL.h>
#include <GameEngine\Entity.h>
#include <GameEngine\Renderer.h>
#include <GameEngine\RenderComponent.h>
#include "ItemSlot.h"

namespace UI
{
	class InterfaceManager
	{
	private:
		std::unordered_map<std::string, GameEngine::RenderComponent*> cache_;
		std::unique_ptr<GameEngine::Renderer> renderer_;
		b2Vec2 windowSize_;
		SDL_Window* window_;
		std::vector<ItemSlot*> actionbarSlots_;
	public:
		InterfaceManager(GameEngine::Renderer* renderer, SDL_Window* window);

		void showHud();

		void showHealth(float maxValue, float value);

		void showActionBar();

		void showInventory();

		void addToActionbar(std::string& texture, int count);

		~InterfaceManager();
	};
}