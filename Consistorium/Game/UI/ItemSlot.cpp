#include "ItemSlot.h"

#include <stdexcept>
#include "../Entities/EntityTypes.h"
#include "../Globals/Constants.h"

namespace UI
{
	ItemSlot::ItemSlot(b2Vec2 itemSize, b2Vec2 itemPos)
		: itemCount_(0)
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
		itemCount_ = 0;
		delete item_.first;
		delete item_.second;
	}

	std::pair<
		Entities::Entity*,
		GameEngine::RenderComponent*> ItemSlot::getItem()
	{
		return item_;
	}

	void ItemSlot::add(int count, Entities::Entity* entity, GameEngine::RenderComponent* rc)
	{
		if (count <= 0)
		{
			throw new std::invalid_argument("Trying to add nothing to the slot.");
		}

		if (!isEmpty() && item_.first->getType() != entity->getType())
		{
			throw new std::invalid_argument("Adding item to an occupied slot.");
		}

		if (isEmpty())
		{
			item_.first = entity;
			item_.second = rc;
		}

		itemCount_ += count;
	}

	void ItemSlot::remove(int count)
	{
		if (itemCount_ < count)
		{
			throw new std::invalid_argument("Trying to remove more items than the slot has.");
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