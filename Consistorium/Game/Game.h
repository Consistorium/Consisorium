#pragma once

#include "SDL/SDL.h"
#include "UI/Window.h"
#include <../GameEngine/Renderer.h>
#include <iostream>

#include "Game.h"
#include "Entities/Player.h"

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks);
void moveCharacter(Player* player, float deltaTicks, int direction);

class Game : public Window
{
private:
	GameEngine::Renderer renderer_;
	void Init();
public:
	Game(SDL_Window* window);

	~Game();

	void Run();
};