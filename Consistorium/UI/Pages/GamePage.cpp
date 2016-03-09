#include "GamePage.h"
#include "../Entities/Player.h"

void handleKeyPress(SDL_Event e);
void moveCharacterLeft();
void moveCharacterRight();
void moveCharacterDown();
void moveCharacterUp();

GamePage::GamePage(SDL_Window* window) 
	: Page(window)
{
}

GamePage::~GamePage()
{
}

void GamePage::Init()
{

}

int speed = 10;

Player player(0, 0, "mainCharacter.png");

void GamePage::Run()
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
				handleKeyPress(e);
			}
		}

		currentTicks = SDL_GetTicks();
		printf("previousTicks: %ld\ncurrentTicks: %ld\n", previousTicks, currentTicks);
		deltaTicks = currentTicks - previousTicks;
		deltaTicks /= 1000;
		SDL_FillRect(windowSurface_, NULL, 0x000000);
		SDL_BlitSurface(player.getModel(), &player.getModel()->clip_rect, windowSurface_, &player.getBounds());
		player.setX(player.getX() + 10 * deltaTicks);
		SDL_UpdateWindowSurface(window_);

		previousTicks = currentTicks;

		auto playerBounds = player.getBounds();
		playerBounds.x = player.getX();
		player.setBounds(playerBounds);
	}
}

void handleKeyPress(SDL_Event e) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		moveCharacterLeft();
		break;
	case SDLK_RIGHT:
		moveCharacterRight();
		break;
	case SDLK_UP:
		moveCharacterUp();
		break;
	case SDLK_DOWN:
		moveCharacterDown();
		break;
	default:
		break;
	}
}

void moveCharacterLeft()
{
	player.setX(player.getX() - speed);
}

void moveCharacterRight()
{
	player.setX(player.getX() + speed);
}

void moveCharacterDown()
{
	player.setY(player.getY() + speed);
}

void moveCharacterUp()
{
	player.setY(player.getY() - speed);
}