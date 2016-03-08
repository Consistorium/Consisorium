#pragma once

#include <SDL.h>

class Page
{
private:
	virtual void Init() = 0;
protected:
	SDL_Window* window_;
	SDL_Surface* windowSurface_;
public:
	Page(SDL_Window* window);
	virtual void Run() = 0;
};