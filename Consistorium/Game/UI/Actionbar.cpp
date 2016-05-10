#include "Actionbar.h"

#include "../Globals/Constants.h"

namespace UI
{
	Actionbar::Actionbar(int slotsCount, int x, int y, int width, int margin)
		: slotCount_(slotsCount)
	{
		int slotDim = width / slotsCount,
			padding = std::ceil((1.0 / 8.0) * slotDim),
			totalSpace = slotsCount * slotDim + (slotsCount - 1) * margin,
			singleHolderSpace = slotDim + margin;

		for (size_t i = 0; i < slotsCount; i++)
		{
			b2Vec2 slotPosition(x + i * singleHolderSpace, y - slotDim);
			b2Vec2 itemPosition(slotPosition.x + padding + 1, slotPosition.y + padding - 1);

			auto slot = new Entities::Entity();
			slot->setPosition(slotPosition);

			auto item = new Entities::Entity();
			item->setPosition(itemPosition);

			auto renderComp = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/ItemHolder__001.png",
				b2Vec2(slotDim, slotDim),
				slot,
				true);

			auto itemRenderComp = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/empty__001.png",
				b2Vec2(slotDim - 2 * padding, slotDim - 2 * padding),
				item,
				true);

			auto slotPair = new std::pair<
				Entities::Entity*,
				GameEngine::RenderComponent*>(
				slot,
				renderComp);

			auto itemPair = new std::pair<
				Entities::Entity*,
				GameEngine::RenderComponent*>(
				item,
				itemRenderComp);

			items_.push_back(itemPair);
			slots_.push_back(slotPair);
		}
	}

	std::vector<
		std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*> *> Actionbar::getSlots()
	{
		return slots_;
	}

	std::vector<
		std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*> *> Actionbar::getItems()
	{
		return items_;
	}

	int Actionbar::getSlotCount() { return slotCount_; }

	Actionbar::~Actionbar()
	{
		slots_.clear();
		items_.clear();
	}
}