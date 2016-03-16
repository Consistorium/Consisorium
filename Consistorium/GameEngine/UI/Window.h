#pragma once

#include <SDL/SDL.h>

class Window
{
private:
	virtual void Init() = 0;
protected:
	SDL_Window* window_;
	SDL_Surface* windowSurface_;
public:
	Window(SDL_Window* window);
	virtual void Run() = 0;
};