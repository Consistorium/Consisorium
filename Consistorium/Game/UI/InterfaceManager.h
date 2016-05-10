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
#include "ItemSlot.h"
#include "Actionbar.h"

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
		void createActionbar();
	public:
		InterfaceManager(GameEngine::Renderer*, SDL_Window*, Entities::Player*);

		void showHud();

		void showHealth(float maxValue, float value);

		void showActionBar();

		//void updateAtionbar();

		void showInventory();

		~InterfaceManager();
	};
}