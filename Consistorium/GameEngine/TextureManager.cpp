#include "TextureManager.h"
#include "../Game/Menu/Menu.h"


TextureManager::TextureManager(SDL_Renderer *renderer)
	: renderer_(renderer)
{
}


TextureManager::~TextureManager()
{
	SDL_DestroyRenderer(renderer_);
	this->renderer_ = nullptr;
}

SDL_Texture* TextureManager::loadTexture(std::string path)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(this->renderer_, loadedSurface);
		if (newTexture == nullptr)
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

b2Vec2* TextureManager::getTextureSize(std::string name)
{
	if (cache_[name] == nullptr)
	{
		cacheTexture(name);
	}

	if (sizeCache_[name] == nullptr)
	{
		int width;
		int height;
		SDL_QueryTexture(getTexture(name), nullptr, nullptr, &width, &height);
		sizeCache_[name] = new b2Vec2(width, height);
	}

	return sizeCache_[name];
}

SDL_Texture* TextureManager::getTexture(std::string path)
{
	if (cache_[path] == nullptr)
	{
		cacheTexture(path);
	}

	return cache_[path];
}
