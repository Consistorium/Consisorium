#pragma once

#include <map>
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>

class TextureManager
{
private:
	SDL_Renderer *renderer_;
	std::map<std::string, SDL_Texture*> cache_;
	std::map<std::string, b2Vec2*> sizeCache_;

	SDL_Texture *loadTexture(std::string path);
public:
	TextureManager(SDL_Renderer *renderer);

	~TextureManager();

	SDL_Texture* getTexture(std::string name);

	b2Vec2* getTextureSize(std::string name);

	void cacheTexture(std::string path);
};