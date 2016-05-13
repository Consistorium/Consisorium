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
#include <Game\Utils\JumpContactListener.h>

namespace Input
{
	class InputHandler
	{
	private:
		b2Timer jumpTimer_;
		b2Timer inventoryTimer_;
	public:
		InputHandler();

		void handleKeyPress(Entities::Player*, KeyboardHandler*, UI::InterfaceManager*, JumpContactListener*, b2Vec2 gravity_);

		void handleMousePress(Entities::Player*, Entities::EntityFactory*, EntityManager*, SDL_Event, b2Vec2 camera);

		~InputHandler();
	};
}