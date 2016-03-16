#include <iostream>

#include "Game.h"
#include "Entities/Player.h"

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks);
void moveCharacterLeft(Player* player, float deltaTicks);
void moveCharacterRight(Player* player, float deltaTicks);

Game::Game(SDL_Window* window)
:Window(window)
{
}

Game::~Game()
{
}

void Game::Init()
{

}

void Game::Run()
{
	Player player(0, 0, "mainCharacter.png", false);

	long previousTicks = 0L;
	long currentTicks = 0L;
	long deltaTicks = 0.0;

	SDL_Event e;

	while (true) {
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				handleKeyPress(e, &player, deltaTicks);
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

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		moveCharacterLeft(player, deltaTicks);
		break;
	case SDLK_RIGHT:
		moveCharacterRight(player, deltaTicks);
		break;
	}
}

void moveCharacterLeft(Player* player, float deltaTicks)
{
	player->setX(player->getX() - player->getSpeed() + player->getSpeed() * deltaTicks);
}

void moveCharacterRight(Player* player, float deltaTicks)
{
	player->setX(player->getX() + player->getSpeed() + player->getSpeed() * deltaTicks);
}