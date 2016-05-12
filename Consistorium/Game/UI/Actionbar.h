#pragma once

#include <vector>
#include <GameEngine\Entity.h>
#include <GameEngine\RenderComponent.h>
#include "../Utils/ItemSlot.h"

namespace UI
{
	class Actionbar
	{
	private:
		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*>*> slots_;

		std::vector<Utils::ItemSlot*> items_;

		b2Vec2 position_;
		b2Vec2 size_;

		int slotCount_;
	public:
		Actionbar(int slotsCount, int x, int y, int width, int margin = 1);

		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> *> getSlots();

		std::vector<Utils::ItemSlot*> getItems();

		int getSlotCount();

		b2Vec2 getPosition();

		b2Vec2 getSize();

		~Actionbar();
	};
}