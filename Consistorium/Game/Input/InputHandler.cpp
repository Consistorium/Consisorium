#include "InputHandler.h"
#include <iostream>
#include <GameEngine\GameEntity.h>
#include <GameState.h>
#include <vector>

namespace Input
{
	InputHandler::InputHandler(KeyboardHandler* keyboardHandler, UI::InterfaceManager* iManager)
		:keyboardHandler_(keyboardHandler),
		interfaceManager_(iManager)
	{
		jumpTimer_.Reset();
		inventoryTimer_.Reset();
	}

	void InputHandler::handleKeyPress(Entities::Player* player, PlayerContactListener* contactListener, b2Vec2 gravity_, long deltaTime)
	{
		if (keyboardHandler_->isPressed(SDLK_LEFT))
		{
			player->setXDirection(LEFT);
			if (!player->leftSensorSensing())
			{
				player->move();
			}
		}
		else if (keyboardHandler_->isPressed(SDLK_RIGHT))
		{
			player->setXDirection(RIGHT);
			if (!player->rightSensorSensing())
			{
				player->move();
			}
		}
		else if (keyboardHandler_->isPressed(SDLK_b))
		{
			if (inventoryTimer_.GetMilliseconds() >= 300)
			{
				interfaceManager_->toggleInventory();
				inventoryTimer_.Reset();
			}
		}

		if (keyboardHandler_->isPressed(SDLK_UP))
		{
			if (player->canJump() && jumpTimer_.GetMilliseconds() > 1.2 * deltaTime)
			{
				player->jump(gravity_);
				jumpTimer_.Reset();
			}
		}

		SDL_Keycode result = keyboardHandler_->isNumberPressed();
		int numberKey = result - SDLK_0;

		if (numberKey > 0 && numberKey <= player->getActionbar().size())
		{
			player->setSelectedItem(interfaceManager_->actionbarSelect(numberKey - 1));
		}
	}

	void InputHandler::handleMousePress(Entities::Player* player, Entities::EntityFactory* entityFactory, EntityManager* eManager, SDL_Event e, b2Vec2 camera)
	{
		SDL_Point clickPoint;
		SDL_GetMouseState(&clickPoint.x, &clickPoint.y);
		b2Vec2 worldCoords = eManager->getWorldCoordinates(clickPoint, camera);
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			if (player->getSelectedItemType() >= 0)
			{
				int type = player->getSelectedItemType(),
					index = player->getSelectedItemIndex();
				if (type > 0)
				{
					entityFactory->createFromName(worldCoords, "", type);
					std::string container = "inventory";
					player->getActionbar();
					
					EventManager::get().signal(ON_PLACE_ITEM, &index);
					if (index >= player->ACTIONBAR_SIZE)
					{
						player->getInventory()[index - player->ACTIONBAR_SIZE]->remove(1);
					}
					else
					{
						player->getActionbar()[index]->remove(1);
					}
				}
			}
			
			return;
		}

		Entities::GameEntity* entity = eManager->getClickedEntity(worldCoords);
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (interfaceManager_->getInventory()->isVisible())
			{
				SDL_Rect inventory;
				inventory.x = interfaceManager_->getInventory()->getPage()->second->getPosition().x;
				inventory.y = interfaceManager_->getInventory()->getPage()->second->getPosition().y;
				inventory.w = interfaceManager_->getInventory()->getPage()->second->getSize().x;
				inventory.h = interfaceManager_->getInventory()->getPage()->second->getSize().y;

				if (SDL_PointInRect(&clickPoint, &inventory))
				{
					b2Vec2 deltaXY(inventory.x - clickPoint.x, inventory.y - clickPoint.y);
					player->setSelectedItem(interfaceManager_->invetorySelect(deltaXY));
				}
			}

			if (entity != nullptr)
			{
				float x1 = entity->getPosition().x;
				float y1 = entity->getPosition().y;
				float x2 = player->getPosition().x;
				float y2 = player->getPosition().y;
				float d = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
				if (d >= player->getRange())
				{
					return;
				}

				if (!EntityTypes::isCognizant(entity->getType()))
				{
					GameState& gameState = GameState::get(player);
					if (!gameState.canBreakEntity(entity)) {
						return;
					}

					int index;
					SlotDescriptor sd;
					sd.entity = entity;
					sd.rc = entity->getRenderableComponent();
					if ((index = player->addToActionbar(entity)) > -1)
					{
						sd.index = index;
						EventManager::get().signal(ON_ACTIONBAR_ADD, &sd);
						eManager->removeFromWorld(entity);
					}
					else if ((index = player->addToInventory(entity)) > -1)
					{
						sd.index = index;
						EventManager::get().signal(ON_INVENTORY_ADD, &sd);
						eManager->removeFromWorld(entity);
					}
				}
				else if (entity->getType() != EntityTypes::Player)
				{
					entity->setHealth(entity->getHealth() - player->getDamage());
					if (entity->getHealth() <= 0)
					{
						GameState::get(player).getEnemyKilledBonus();
						EventManager::get().signal(ON_REMOVE_ENTITY, entity);
						eManager->removeFromWorld(entity);
					}
				}
			}
				
		}
	}

	InputHandler::~InputHandler()
	{
	}
}