#include "ItemSlot.h"

#include <stdexcept>
#include "../Entities/EntityTypes.h"
#include "../Globals/Constants.h"

namespace Utils
{
	ItemSlot::ItemSlot(b2Vec2 itemSize, b2Vec2 itemPos, int count)
		: itemCount_(count),
		maxItemCount_(MAX_ITEM_COUNT)
	{
		auto item = new Entities::Entity();
		item->setPosition(itemPos);
		item->setType((int)EntityTypes::PositionEntity);

		auto itemRenderComp = new GameEngine::RenderComponent(
			Globals::MODELS_LOCATION + "Common/empty__001.png",
			itemSize,
			item,
			true);

		item_ = std::pair<Entities::Entity*, GameEngine::RenderComponent*>(item, itemRenderComp);
	}

	bool ItemSlot::isEmpty()
	{
		return itemCount_ == 0;
	}

	void ItemSlot::setTexture(std::string texture)
	{
		item_.second->setTextureName(texture);
	}

	void ItemSlot::empty()
	{
		item_.second->setTextureName(Globals::MODELS_LOCATION + "Common/empty__001.png");
		item_.first->setType(EntityTypes::Nothing);
	}

	int ItemSlot::getCount()
	{
		return itemCount_;
	}

	std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*> ItemSlot::getItem()
	{
		return item_;
	}

	bool  ItemSlot::tryAdd(int count, Entities::Entity* entity, GameEngine::IRenderable* rc)
	{
		if (count <= 0)
		{
			throw new std::invalid_argument("Trying to add nothing to the slot.");
		}

		if ((!isEmpty() && 
			item_.first->getType() != entity->getType()) ||
			(itemCount_ + count > maxItemCount_))
		{
			return false;
		}

		if (isEmpty())
		{
			item_.first->setType(entity->getType());
			item_.second->setTextureName(*rc->getTextureName());
		}

		itemCount_ += count;
		return true;
	}

	void ItemSlot::remove(int count)
	{
		if (itemCount_ < count)
		{
			//throw new std::invalid_argument("Trying to remove more items than the slot has.");
			return;
		}

		itemCount_ -= count;

		if (itemCount_ == 0) 
		{
			empty();
		}
	}

	ItemSlot::~ItemSlot()
	{
	}
}