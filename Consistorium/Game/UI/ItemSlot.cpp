#include "ItemSlot.h"

#include <stdexcept>

namespace UI
{
	ItemSlot::ItemSlot(b2Vec2 position)
	{
		position_ = position;
		itemCount_ = 0;
	}

	bool ItemSlot::isEmpty()
	{
		return itemCount_ == 0;
	}

	void ItemSlot::empty()
	{
		itemCount_ = 0;
	}

	void ItemSlot::add(int count, std::string itemTexture)
	{
		if (!isEmpty() && itemTexture != itemTexture_)
		{
			throw new std::invalid_argument("Adding item to an occupied slot.");
		}

		if (isEmpty())
		{
			itemTexture_ = itemTexture;
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

	std::string ItemSlot::getItemTexture()
	{
		return itemTexture_;
	}

	void ItemSlot::setTexture(std::string texture)
	{
		itemTexture_ = texture;
	}

	b2Vec2 ItemSlot::getPosition()
	{
		return position_;
	}

	ItemSlot::~ItemSlot()
	{
	}
}