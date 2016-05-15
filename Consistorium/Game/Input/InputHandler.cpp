#include "InputHandler.h"
#include <iostream>
namespace Input
{
	InputHandler::InputHandler()
	{
		jumpTimer_.Reset();
		inventoryTimer_.Reset();
	}

	void InputHandler::handleKeyPress(Entities::Player* player, KeyboardHandler* keyboardHandler, UI::InterfaceManager* interfaceManager, PlayerContactListener* contactListener, b2Vec2 gravity_, long deltaTime)
	{
		if (keyboardHandler->isPressed(SDLK_LEFT))
		{
			player->setXDirection(LEFT);
			player->move();
		}
		else if (keyboardHandler->isPressed(SDLK_RIGHT))
		{
			player->setXDirection(RIGHT);
			player->move();
		}
		else if (keyboardHandler->isPressed(SDLK_b))
		{
			if (inventoryTimer_.GetMilliseconds() >= 300)
			{
				interfaceManager->toggleInventory();
				inventoryTimer_.Reset();
			}
		}

		if (keyboardHandler->isPressed(SDLK_UP))
		{
			if (player->canJump() && jumpTimer_.GetMilliseconds() > 1.2 * deltaTime)
			{
				player->jump(gravity_);
				jumpTimer_.Reset();
			}
		}
	}

	void InputHandler::handleMousePress(Entities::Player* player, Entities::EntityFactory* entityFactory, EntityManager* eManager, SDL_Event e, b2Vec2 camera)
	{
		SDL_Point clickPoint;
		SDL_GetMouseState(&clickPoint.x, &clickPoint.y);
		b2Vec2 worldCoords = eManager->getWorldCoordinates(clickPoint, camera);
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			entityFactory->createBlock(worldCoords, "Grass");
			return;
		}

		Entities::GameEntity* entity = eManager->getClickedEntity(worldCoords);

		if (entity != nullptr)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (!EntityTypes::isCognizant(entity->getType()))
				{
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
			}
		}
	}

	InputHandler::~InputHandler()
	{
	}
}