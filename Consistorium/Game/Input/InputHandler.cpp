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
			if (!player->leftSensorSensing())
			{
				player->move();
			}
		}
		else if (keyboardHandler->isPressed(SDLK_RIGHT))
		{
			player->setXDirection(RIGHT);
			if (!player->rightSensorSensing())
			{
				player->move();
			}
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