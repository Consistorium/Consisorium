#pragma once

#include "SDL/SDL.h"
#include "UI/Window.h"

class Game : public Window
{
private:
	void Init();
public:
	Game(SDL_Window* window);

	~Game();

	void Run();
};