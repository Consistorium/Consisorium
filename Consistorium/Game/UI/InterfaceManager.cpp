#include "InterfaceManager.h"

#include <string>
#include <vector>
#include <SDL\SDL_image.h>
#include <Game\Globals\Constants.h>

namespace UI
{
	InterfaceManager::InterfaceManager(SDL_Surface* surface)
		:surface_(surface)
	{
	}

	void InterfaceManager::showHud()
	{
		
	}

	void InterfaceManager::showHealth(float maxValue, float value)
	{
	}

	void InterfaceManager::showActionBar()
	{

	}

	void InterfaceManager::showInventory()
	{

	}

	InterfaceManager::~InterfaceManager()
	{

	}
}