#pragma once

#include "SDL.h"
#include "Page.h"

class GamePage : public Page
{
private:
	void Init();
public:
	GamePage(SDL_Window* window);

	~GamePage();

	void Run();
};