#pragma once

#include <Game\Entities\Player.h>
#include <GameEngine\DynamicEntity.h>
#include <Game\Entities\EntityFactory.h>
#include <GameEngine\EntityManager.h>
#include <GameEngine\EventManager.h>
#include <Game\Entities\EntityTypes.h>
#include <Game\Utils\SlotDescriptor.h>
#include <Game\EventIds.h>
#include <Game\UI\InterfaceManager.h>
#include <GameEngine\KeyboardHandler.h>
#include <Game\Utils\PlayerContactListener.h>
#include <Game\Utils\Directions.h>

namespace Input
{
	class InputHandler
	{
	private:
		b2Timer jumpTimer_;
		b2Timer inventoryTimer_;
	public:
		InputHandler();

		void handleKeyPress(Entities::Player*, KeyboardHandler*, UI::InterfaceManager*, PlayerContactListener*, b2Vec2 gravity_, long deltaTime);

		void handleMousePress(Entities::Player*, Entities::EntityFactory*, EntityManager*, SDL_Event, b2Vec2 camera);

		~InputHandler();
	};
}