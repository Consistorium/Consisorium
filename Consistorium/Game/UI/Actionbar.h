#pragma once

#include <vector>
#include <GameEngine\Entity.h>
#include <GameEngine\RenderComponent.h>

namespace UI
{
	class Actionbar
	{
	private:
		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*>*> slots_;

		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> *> items_;

		int slotCount_;
	public:
		Actionbar(int slotsCount, int x, int y, int width, int margin = 1);

		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> *> getSlots();

		std::vector<
			std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> *> getItems();

		int getSlotCount();

		~Actionbar();
	};
}