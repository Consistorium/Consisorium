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
		int windowX, windowY;
		SDL_GetWindowSize(window_, &windowX, &windowY);
		int width = 400,
			slotsCount = 8,
			slotDim = width / slotsCount,
			x = (windowX - width) / 2,
			y = windowY - slotDim;
		actionbar_ = std::make_unique<Actionbar>(Actionbar(8, x, y, width));
	}

	void InterfaceManager::showActionBar()
	{
		for (int i = 0; i < actionbar_->getSlotCount(); i++)
		{
			renderer_->AddRenderable(UI_Z_INDEX, actionbar_->getSlots()[i]->second);
			renderer_->AddRenderable(UI_Z_INDEX + 1, actionbar_->getItems()[i]->second);
		}
	}

	/*void InterfaceManager::updateAtionbar()
	{
		for (size_t i = 0; i < player_->getActionbar().size(); i++)
		{
			abItems_[i]->second->setTextureName(
				*player_->getActionbar()[i]
				->getRenderableComponent()
				->getTextureName());
		}
	}*/

	void InterfaceManager::showInventory()
	{

	}

	InterfaceManager::~InterfaceManager()
	{
		
	}
}