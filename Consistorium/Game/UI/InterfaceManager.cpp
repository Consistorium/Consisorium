#include "InterfaceManager.h"

#include <string>
#include <GameEngine\RenderComponent.h>
#include <Game\Globals\Constants.h>

namespace UI
{
	
	const int UI_Z_INDEX = 100;

	InterfaceManager::InterfaceManager(GameEngine::Renderer* renderer, SDL_Window* window, Entities::Player* player)
		:renderer_(renderer),
		window_(window),
		player_(std::shared_ptr<Entities::Player>(player)),
		inventory_(std::make_unique<Inventory>(Inventory(player_->INVENTORY_SIZE)))
	{
		createActionbar();
		inventoryPage_;
	}

	void InterfaceManager::showHud()
	{
		
	}

	void InterfaceManager::toggleInventory()
	{
		if (inventory_->isVisible())
		{
			inventory_->hide(renderer_.get(), UI_Z_INDEX);
		}
		else
		{
			int windowX, windowY;
			SDL_GetWindowSize(window_, &windowX, &windowY);
			b2Vec2 size = b2Vec2(windowX / 6, windowY / 6),
				pos = b2Vec2(windowX - size.x - 20, windowY - size.y - actionbar_->getSize().y * 2);
			inventory_->show(pos, size, renderer_.get(), UI_Z_INDEX);
		}
	}

	void InterfaceManager::showHealth(float maxValue, float value)
	{
	}

	void InterfaceManager::createActionbar()
	{
		int windowX, windowY;
		SDL_GetWindowSize(window_, &windowX, &windowY);
		int width = windowX / 4,
			slotsCount = player_->ACTIONBAR_SIZE,
			slotDim = width / slotsCount,
			x = (windowX - width) / 2,
			y = windowY - slotDim;
		actionbar_ = std::make_unique<Actionbar>(Actionbar(slotsCount, x, y, width));
	}

	void InterfaceManager::showActionBar()
	{
		for (int i = 0; i < actionbar_->getSlotCount(); i++)
		{
			renderer_->AddRenderable(UI_Z_INDEX, actionbar_->getSlots()[i]->second);
			renderer_->AddRenderable(UI_Z_INDEX + 1, actionbar_->getItems()[i]->getItem().second);
		}
	}

	void InterfaceManager::update()
	{
		b2Vec2 newScale(0, 0);

		for (size_t i = 0; i < player_->getActionbar().size(); i++)
		{
			GameEngine::IRenderable* rc =
				player_->getActionbar()[i]
				->getItem().second;

			int zIndex = rc->getZIndex();

			actionbar_
				->getItems()[i]
				->getItem()
				.second
				->setTextureName(*rc->getTextureName());

			renderer_->RemoveRenderable(zIndex, rc);
		}

		for (size_t i = 0; i < player_->getInventory().size(); i++)
		{
			GameEngine::IRenderable* rc = player_
				->getInventory()[i]
				->getItem().second;

			int zIndex = rc->getZIndex();

			inventory_
				->getItems()[i]
				->getItem()
				.second
				->setTextureName(*rc->getTextureName());

			renderer_->RemoveRenderable(zIndex, rc);
		}
	}

	InterfaceManager::~InterfaceManager()
	{
		
	}
}