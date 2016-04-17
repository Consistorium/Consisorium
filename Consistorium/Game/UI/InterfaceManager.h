#pragma once

#include <SDL\SDL.h>
#include <TextureManager.h>

namespace UI
{
	class InterfaceManager
	{
	private:
		SDL_Surface* surface_;
	public:
		InterfaceManager(SDL_Surface* surface);

		void showHud();

		void showHealth(SDL_Rect position, std::string bar, float maxValue, float value);

		void showActionBar();

		void showInventory();

		~InterfaceManager();
	};
}