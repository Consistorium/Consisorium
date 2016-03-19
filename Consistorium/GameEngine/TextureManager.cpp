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

SDL_Texture* TextureManager::getTexture(char *path)
{
	if (cache_[path] != NULL)
	{
		return cache_[path];
	}

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	// For debugging
	printf("Loading a texture again. Not using cache. Wrong!");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(this->renderer_, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	cache_[path] = newTexture;

	return newTexture;
}