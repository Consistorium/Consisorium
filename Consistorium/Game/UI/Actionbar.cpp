#include "Actionbar.h"

#include "../Globals/Constants.h"

namespace UI
{
	Actionbar::Actionbar(int slotsCount, int x, int y, int width, int margin)
		: slotCount_(slotsCount),
		position_(b2Vec2(x, y))
	{
		int slotDim = width / slotsCount,
			padding = std::ceil((1.0 / 8.0) * slotDim),
			totalSpace = slotsCount * slotDim + (slotsCount - 1) * margin,
			singleHolderSpace = slotDim + margin;

		size_ = b2Vec2(slotDim, slotDim);

		for (size_t i = 0; i < slotsCount; i++)
		{
			b2Vec2 slotPosition(x + i * singleHolderSpace, y);
			b2Vec2 itemPosition(slotPosition.x + padding + 1, slotPosition.y + padding - 1);

			auto slot = new Entities::Entity();
			slot->setPosition(slotPosition);

			auto renderComp = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/ItemHolder__001.png",
				b2Vec2(slotDim, slotDim),
				slot,
				true);

			auto slotPair = new std::pair<
				Entities::Entity*,
				GameEngine::RenderComponent*>(
				slot,
				renderComp);

			auto itemSlot = new Utils::ItemSlot(b2Vec2(slotDim - 2 * padding, slotDim - 2 * padding), itemPosition);

			items_.push_back(itemSlot);
			slots_.push_back(slotPair);
		}
	}

	b2Vec2 Actionbar::getPosition() { return position_; }

	b2Vec2 Actionbar::getSize() { return size_; }

	std::vector<
		std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*> *> Actionbar::getSlots()
	{
		return slots_;
	}

	std::vector<Utils::ItemSlot*> Actionbar::getItems()
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