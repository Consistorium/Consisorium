#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <SDL\SDL.h>
#include <TextureManager.h>

namespace UI
{
	class InterfaceManager
	{
	private:
		std::unordered_map<std::string, SDL_Texture*> cache_;
		SDL_Surface* surface_;
	public:
		InterfaceManager(SDL_Surface* surface);

		void showHud();

		void showHealth(float maxValue, float value);

		void showActionBar();

		void showInventory();

		~InterfaceManager();
	};
}