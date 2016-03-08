#include "GamePage.h"
#include "../Entities/Player.h"

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

void GamePage::Run()
{
	long previousTicks = 0L;
	long currentTicks = 0L;
	long deltaTicks = 0.0;

	Player player(0, 0, "mainCharacter.png");

	while (true) {
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