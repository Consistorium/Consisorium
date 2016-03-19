#include "Game.h"

Game::Game(SDL_Window* window)
	:Window(window),
	renderer_(window)
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
	GameEngine::Vector2D playerPosition(0, 0);
	Player player(playerPosition, "mainCharacter.png");

	double previousTicks = 0L;
	double currentTicks = 0L;
	double deltaTicks = 0.0;

	SDL_Event e;

	renderer_.AddRenderable(&player);

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
		if (deltaTicks == 0)
		{
			deltaTicks = 1;
		}
		deltaTicks /= 1000;

		renderer_.RenderAll();

		previousTicks = currentTicks;
	}
}

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		moveCharacter(player, deltaTicks, -1);
	case SDLK_RIGHT:
		moveCharacter(player, deltaTicks, 1);
		break;
	}
}

void moveCharacter(Player* player, float deltaTicks, int direction)
{
	GameEngine::Vector2D p = player->getPosition();
	p.SetXY(p.X() + direction * player->getSpeed() * deltaTicks, p.Y());
	player->setPosition(p);
}