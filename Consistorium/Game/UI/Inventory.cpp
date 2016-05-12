#include "Inventory.h"

#include "../Globals/Constants.h"

namespace UI
{
	const b2Vec2 SIZE_DELIMITER(6, 3);
	const int DEFAULT_WIDTH = 300;
	const int DEFAULT_HEIGHT = 200;
	const int MARGIN_DELIMITER = 94;

	Inventory::Inventory(int slotCount)
		: slotCount_(slotCount),
		visible_(false),
		slotsPerLine_(6)
	{
		b2Vec2 pos = b2Vec2(0, 0),
			size = b2Vec2(400, 400),
			slotDim(size.x / SIZE_DELIMITER.x, size.y / SIZE_DELIMITER.y);

		int margin = ceil(size.x / MARGIN_DELIMITER);

		auto inventory = new Entities::Entity();
		inventory->setPosition(b2Vec2(0, 0));

		auto renderComp = new GameEngine::RenderComponent(
			Globals::MODELS_LOCATION + "Common/Inventory__001.png",
			b2Vec2(DEFAULT_WIDTH, DEFAULT_HEIGHT),
			inventory,
			true);

		inventoryPage_ = std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*>(
			inventory,
			renderComp);

		for (size_t i = 0; i < slotCount_; i++)
		{
			b2Vec2 itemPosition = b2Vec2(
				pos.x + (i % slotsPerLine_) * slotDim.x + (i > 1 && (i % slotsPerLine_) != 0 ? margin : 0),
				pos.y + i / slotsPerLine_ * slotDim.y);

			auto itemSlot = new Utils::ItemSlot(b2Vec2(slotDim.x - 2, slotDim.y - 2), itemPosition);
			items_.push_back(itemSlot);
		}
	}

	void Inventory::show(b2Vec2 pos, b2Vec2 size, GameEngine::Renderer* renderer, int index)
	{
		visible_ = true;
		int lines = (slotCount_ / slotsPerLine_),
			margin = ceil(size.x / MARGIN_DELIMITER),
			marginYSubtrahend = (lines - 1) * margin / lines,
			marginXSubtrahend = (slotsPerLine_ - 1) * margin / slotsPerLine_;

		b2Vec2 oldSize = inventoryPage_.second->getSize(),
			   slotDim(
				   size.x / SIZE_DELIMITER.x - marginXSubtrahend, 
				   size.y / SIZE_DELIMITER.y - marginYSubtrahend);

		inventoryPage_.first->setPosition(pos);
		inventoryPage_.second->setScale(b2Vec2(size.x / oldSize.x, size.y / oldSize.y));
		renderer->AddRenderable(index, inventoryPage_.second);

		for (size_t i = 0; i < slotCount_; i++)
		{
			b2Vec2 itemPosition = b2Vec2(
				pos.x + (i % slotsPerLine_) * (slotDim.x + margin),
				pos.y + i / slotsPerLine_ * (slotDim.y + margin));

			items_[i]->getItem().first->setPosition(itemPosition);
			auto itemRC = items_[i]->getItem().second;
			b2Vec2 textureSize = itemRC->getSize();

			itemRC->setScale(b2Vec2(slotDim.x / textureSize.x, slotDim.y / textureSize.y));
			renderer->AddRenderable(index + 1, itemRC);
		}
	}

	bool Inventory::isVisible() { return visible_; }

	void Inventory::hide(GameEngine::Renderer* renderer, int index)
	{
		visible_ = false;
		renderer->RemoveRenderable(index, inventoryPage_.second);
		for (size_t i = 0; i < items_.size(); i++)
		{
			renderer->RemoveRenderable(index, items_[i]->getItem().second);
		}
	}

	std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*>* Inventory::getPage()
	{
		return &inventoryPage_;
	}

	std::vector<Utils::ItemSlot*> Inventory::getItems()
	{
		return items_;
	}

	Inventory::~Inventory()
	{

	}
}