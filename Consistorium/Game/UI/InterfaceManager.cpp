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

	void InterfaceManager::showHealth(SDL_Rect position, std::string bar, float maxValue, float value)
	{
		float denominator = maxValue / 20;
		int textureNumber = ceil(value / denominator);
		std::string texture = Globals::MODELS_LOCATION + "Common/Bars/" + bar + "_" + std::to_string(textureNumber) + ".png";
		SDL_Surface* barSurface = IMG_Load(texture.c_str());
		SDL_BlitSurface(barSurface, &barSurface->clip_rect, surface_, &position);
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