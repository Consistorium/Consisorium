#pragma once

#include <string>
#include <vector>
#include <GameEngine\Entity.h>
#include <GameEngine\RenderComponent.h>
#include <GameEngine\Renderer.h>
#include "../Utils/ItemSlot.h"

namespace UI
{
	class Inventory
	{
	private:
		int slotCount_,
			slotsPerLine_;
		bool visible_;
		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> inventoryPage_;

		std::vector<Utils::ItemSlot*> items_;
	public:
		Inventory(int slotCount);

		void show(b2Vec2 pos, b2Vec2 size, GameEngine::Renderer* renderer, int index);

		void hide(GameEngine::Renderer* renderer, int index);

		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*>* getPage();

		std::vector<Utils::ItemSlot*> getItems();

		~Inventory();

		bool isVisible();
	};
}