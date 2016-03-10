#include <iostream>

#include "Engine.h"
#include "../Entities/Player.h"
#include "PlayerMovementManager.h"

void handleKeyPress(SDL_Event e, float deltaTicks);

Engine::Engine(SDL_Window* window)
	: Page(window)
{
}

Engine::~Engine()
{
}

void Engine::Init()
{

}

Player player(0, 0, "mainCharacter.png", false);
PlayerMovementManager playerMovementManager;

void Engine::Run()
{
	long previousTicks = 0L;
	long currentTicks = 0L;
	long deltaTicks = 0.0;

	SDL_Event e;

	while (true) {
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				handleKeyPress(e, deltaTicks);
			}
		}

		currentTicks = SDL_GetTicks();
		deltaTicks = currentTicks - previousTicks;
		deltaTicks /= 1000;
		SDL_FillRect(windowSurface_, NULL, 0x000000);
		SDL_BlitSurface(player.getModel(), &player.getModel()->clip_rect, windowSurface_, &player.getBounds());
		SDL_UpdateWindowSurface(window_);

		previousTicks = currentTicks;

		auto playerBounds = player.getBounds();
		playerBounds.x = player.getX();
		playerBounds.y = player.getY();
		player.setBounds(playerBounds);
	}
}

void handleKeyPress(SDL_Event e, float deltaTicks) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
		playerMovementManager.handleMovement(e.key.keysym.sym, &player, deltaTicks);
		break;
	}
}