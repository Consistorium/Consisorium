#pragma once

#include "SDL.h"
#include "../Page.h"

class Engine : public Page
{
private:
	void Init();
public:
	Engine(SDL_Window* window);

	~Engine();

	void Run();
};