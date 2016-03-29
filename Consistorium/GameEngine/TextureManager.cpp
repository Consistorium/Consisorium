#include "TextureManager.h"


TextureManager::TextureManager(SDL_Renderer *renderer)
	: renderer_(renderer)
{
}


TextureManager::~TextureManager()
{
	SDL_DestroyRenderer(renderer_);
	this->renderer_ = NULL;
}

SDL_Texture* TextureManager::loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(this->renderer_, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}



void TextureManager::cacheTexture(std::string path)
{
	SDL_Texture *texture = this->loadTexture(path);
	cache_[path] = texture;
}

SDL_Texture* TextureManager::getTexture(std::string path)
{
	if (cache_[path] == NULL)
	{
		cacheTexture(path);
	}

	return cache_[path];
}