#include "InterfaceManager.h"

#include <string>
#include <GameEngine\RenderComponent.h>
#include <Game\Globals\Constants.h>

namespace UI
{
	const int ITEM_HOLDER_DIM = 50;
	const int ITEM_HOLDER_MARGIN = 10;
	const int ITEM_HOLDER_COUNT = 8;
	const int UI_Z_INDEX = 100;
	const int SLOT_PADDING = std::ceil((1.0 / 8.0) * 50.0);

	InterfaceManager::InterfaceManager(GameEngine::Renderer* renderer, SDL_Window* window)
		:renderer_(renderer),
		window_(window)
	{

	}

	void InterfaceManager::showHud()
	{
		
	}

	void InterfaceManager::showHealth(float maxValue, float value)
	{
	}

	void InterfaceManager::addToActionbar(std::string& texture, int count)
	{
		for (size_t i = 0; i < actionbarSlots_.size(); i++)
		{
			if (actionbarSlots_[i]->isEmpty())
			{
				b2Vec2 itemPosition(
					actionbarSlots_[i]->getPosition().x + SLOT_PADDING + 2,
					actionbarSlots_[i]->getPosition().y + SLOT_PADDING - 1);
				actionbarSlots_[i]->add(count, texture);
				Entities::Entity* item = new Entities::Entity();
				//TODO: Change to get item render position
				item->setPosition(itemPosition);
				GameEngine::RenderComponent* rc = new GameEngine::RenderComponent(
					texture,
					b2Vec2(ITEM_HOLDER_DIM - 2 * SLOT_PADDING, ITEM_HOLDER_DIM - 2 * SLOT_PADDING),
					item);

				rc->setAlwaysRender(true);
				rc->forEntity(item);

				//std::pair<std::string, GameEngine::RenderComponent*> pair("ItemHolder", rc);
				//cache_.insert(pair);
				renderer_->AddRenderable(UI_Z_INDEX + 1, rc);

				break;
			}
			else if (actionbarSlots_[i]->getItemTexture() == texture)
			{
				actionbarSlots_[i]->add(count, texture);
				break;
			}
		}
	}

	void InterfaceManager::showActionBar()
	{
		int totalSpace = ITEM_HOLDER_COUNT * ITEM_HOLDER_DIM + (ITEM_HOLDER_COUNT - 1) * ITEM_HOLDER_MARGIN;
		int singleHolderSpace = ITEM_HOLDER_DIM + ITEM_HOLDER_MARGIN;
		int windowX, windowY;
		SDL_GetWindowSize(window_, &windowX, &windowY);
		int x = (windowX - totalSpace) / 2;
		for (size_t i = 0; i < ITEM_HOLDER_COUNT; i++)
		{
			b2Vec2 itemPosition(x + i * singleHolderSpace, windowY - ITEM_HOLDER_DIM);

			ItemSlot* slot = new ItemSlot(itemPosition);
			actionbarSlots_.push_back(slot);

			Entities::Entity* item = new Entities::Entity();
			item->setPosition(itemPosition);
			GameEngine::RenderComponent* rc = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/ItemHolder__001.png",
				b2Vec2(ITEM_HOLDER_DIM, ITEM_HOLDER_DIM),
				item);

			rc->setAlwaysRender(true);
			rc->forEntity(item);

			std::pair<std::string, GameEngine::RenderComponent*> pair("ItemHolder", rc);
			cache_.insert(pair);
			renderer_->AddRenderable(UI_Z_INDEX, rc);
		}
	}

	void InterfaceManager::showInventory()
	{

	}

	InterfaceManager::~InterfaceManager()
	{

	}
}