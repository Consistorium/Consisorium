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

	InterfaceManager::InterfaceManager(GameEngine::Renderer* renderer, SDL_Window* window, Entities::Player* player)
		:renderer_(renderer),
		window_(window),
		player_(std::shared_ptr<Entities::Player>(player))
	{
		createActionbar();
	}

	void InterfaceManager::showHud()
	{
		
	}

	void InterfaceManager::showHealth(float maxValue, float value)
	{
	}

	void InterfaceManager::createActionbar()
	{
		int totalSpace = ITEM_HOLDER_COUNT * ITEM_HOLDER_DIM + (ITEM_HOLDER_COUNT - 1) * ITEM_HOLDER_MARGIN;
		int singleHolderSpace = ITEM_HOLDER_DIM + ITEM_HOLDER_MARGIN;
		int windowX, windowY;
		SDL_GetWindowSize(window_, &windowX, &windowY);
		int x = (windowX - totalSpace) / 2;

		for (size_t i = 0; i < player_->ACTIONBAR_SIZE; i++)
		{
			b2Vec2 slotPosition(x + i * singleHolderSpace, windowY - ITEM_HOLDER_DIM);
			b2Vec2 itemPosition(slotPosition.x + SLOT_PADDING + 1, slotPosition.y + SLOT_PADDING - 1);

			auto slot = new Entities::Entity();
			slot->setPosition(slotPosition);
			
			auto item = new Entities::Entity();
			item->setPosition(itemPosition);

			auto renderComp = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/ItemHolder__001.png", 
				b2Vec2(ITEM_HOLDER_DIM, ITEM_HOLDER_DIM),
				slot,
				true);

			auto itemRenderComp = new GameEngine::RenderComponent(
				Globals::MODELS_LOCATION + "Common/empty__001.png",
				b2Vec2(ITEM_HOLDER_DIM - 2 * SLOT_PADDING, ITEM_HOLDER_DIM - 2 * SLOT_PADDING),
				item,
				true);
			
			auto slotPair = new std::pair<
				Entities::Entity*, 
				GameEngine::RenderComponent*> (
					slot,
					renderComp);

			auto itemPair = new std::pair<
				Entities::Entity*,
				GameEngine::RenderComponent*>(
					item,
					itemRenderComp);

			abItems_.push_back(itemPair);
			actionbar_.push_back(slotPair);
		}
	}

	void InterfaceManager::showActionBar()
	{
		for (int i = 0; i < actionbar_.size(); i++)
		{
			renderer_->AddRenderable(UI_Z_INDEX, actionbar_[i]->second);
			renderer_->AddRenderable(UI_Z_INDEX + 1, abItems_[i]->second);
		}
	}

	void InterfaceManager::updateAtionbar()
	{
		for (size_t i = 0; i < player_->getActionbar().size(); i++)
		{
			abItems_[i]->second->setTextureName(
				*player_->getActionbar()[i]
				->getRenderableComponent()
				->getTextureName());
		}
	}

	void InterfaceManager::showInventory()
	{

	}

	InterfaceManager::~InterfaceManager()
	{
		actionbar_.clear();
		abItems_.clear();
	}
}