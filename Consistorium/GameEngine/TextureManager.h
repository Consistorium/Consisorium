#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <memory>
#include "IGraphicsRenderer.h"
#include <stdio.h>
#include <map>

class TextureManager
{
private:
	SDL_Renderer *renderer_;
	std::map<std::string, SDL_Texture*> cache_;

	SDL_Texture *loadTexture(std::string path);
public:
	TextureManager(SDL_Renderer *renderer);

	~TextureManager();

	SDL_Texture* getTexture(std::string name);

	void cacheTexture(std::string path);
};

