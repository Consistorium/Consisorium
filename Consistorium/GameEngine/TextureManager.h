#pragma once

#include <stdio.h>
#include <map>
#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "IGraphicsRenderer.h"

class TextureManager
{
private:
	SDL_Renderer *renderer_;
	std::map<char*, SDL_Texture*> cache_;
public:
	TextureManager(SDL_Renderer *renderer);
	~TextureManager();

	SDL_Texture* getTexture(char *path);
};

