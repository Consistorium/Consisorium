#include "InterfaceManager.h"

#include <string>
#include <GameEngine\RenderComponent.h>
#include <Game\Globals\Constants.h>
#include <Game\EventIds.h>
#include <Game\Entities\EntityTypes.h>

namespace UI
{
	InterfaceManager::InterfaceManager(GameEngine::Renderer* renderer, SDL_Window* window, Entities::Player* player, EventManager& eManager)
		:renderer_(renderer),
		window_(window),
		player_(std::shared_ptr<Entities::Player>(player)),
		inventory_(std::make_unique<Inventory>(Inventory(player_->INVENTORY_SIZE)))
	{
		createActionbar();
		inventoryPage_;
		eManager.addWithParams(ON_ACTIONBAR_ADD, [&](void* param) {
			auto sd = (SlotDescriptor*)(param);
			actionbar_->getItems()[sd->index]->tryAdd(1, sd->entity, sd->rc);
			return nullptr;
		});

		eManager.addWithParams(ON_INVENTORY_ADD, [&](void* param) {
			auto sd = (SlotDescriptor*)(param);
			inventory_->getItems()[sd->index]->tryAdd(1, sd->entity, sd->rc);
			return nullptr;
		});

		EventManager::get().addWithParams(
			ON_PLACE_ITEM,
			[&](void* arg)
			{
				int index = *(int*)(arg);
				int actionbarSlotsCount = actionbar_->getSlotCount();
				if (index >= actionbarSlotsCount)
				{
					int inventoryIndex = index - actionbarSlotsCount;
					if (inventory_->getItems()[inventoryIndex]->getCount() <= 0)
					{
						return nullptr;
					}

					inventory_->getItems()[inventoryIndex]->remove(1);
					if (inventory_->getItems()[inventoryIndex]->isEmpty())
					{
						player_->setSelectedItem(std::pair<int, int>((int)EntityTypes::Nothing, index));
					}
				}
				else
				{
					if (actionbar_->getItems()[index]->getCount() <= 0)
					{
						return nullptr;
					}

					actionbar_->getItems()[index]->remove(1);
					if (actionbar_->getItems()[index]->isEmpty())
					{
						std::pair<int, int> a((int)EntityTypes::Nothing, index);
						player_->setSelectedItem(a);
					}
				}

				return nullptr;
			});
	}

	void InterfaceManager::showHud()
	{
		
	}

	void InterfaceManager::toggleInventory()
	{
		if (inventory_->isVisible())
		{
			inventory_->hide(renderer_.get(), Globals::UI_Z_INDEX);
		}
		else
		{
			int windowX, windowY;
			SDL_GetWindowSize(window_, &windowX, &windowY);
			b2Vec2 size = b2Vec2(windowX / 6, windowY / 6),
				pos = b2Vec2(windowX - size.x - 20, windowY - size.y - actionbar_->getSize().y * 2);
			inventory_->show(pos, size, renderer_.get(), Globals::UI_Z_INDEX);
		}
	}

	void InterfaceManager::showHealth(float maxValue, float value)
	{
	}

	std::pair<int, int> InterfaceManager::invetorySelect(b2Vec2 clickPoint)
	{
		clickPoint.x = abs(clickPoint.x);
		clickPoint.y = abs(clickPoint.y);
		b2Vec2 slotDim = inventory_->getSlotDim();
		int x = ceil(clickPoint.x / (slotDim.x + inventory_->getSlotMargin()));
		int y = ceil(clickPoint.y / slotDim.y);
		int index = (y - 1) * inventory_->getSlotsPerLine() + x - 1;
		if (index > 17)
		{
			index = 17;
		}

		int entityType = inventory_->getItems()[index]->getItem().first->getType();
		GameEngine::RenderComponent* rc = inventory_->getItems()[index]->getItem().second;
		return std::pair<int, int>(entityType, index + actionbar_->getSlotCount());
	}

	std::pair<int, int> InterfaceManager::actionbarSelect(int index)
	{
		int entityType = actionbar_->getItems()[index]->getItem().first->getType();
		return std::pair<int, int>(entityType, index);
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
			renderer_->AddRenderable(Globals::UI_Z_INDEX, actionbar_->getSlots()[i]->second);
			renderer_->AddRenderable(Globals::UI_Z_INDEX + 1, actionbar_->getItems()[i]->getItem().second);
		}
	}

	Actionbar* InterfaceManager::getActionbar()
	{
		return actionbar_.get();
	}

	Inventory* InterfaceManager::getInventory()
	{
		return inventory_.get();
	}

	InterfaceManager::~InterfaceManager()
	{
		
	}
}