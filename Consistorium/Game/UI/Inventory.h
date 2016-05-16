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
			slotsPerLine_,
			slotMargin_;
		bool visible_;

		b2Vec2 slotDim_;

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

		int getSlotsPerLine();

		b2Vec2 getSlotDim();

		int getSlotMargin();

		~Inventory();

		bool isVisible();
	};
}