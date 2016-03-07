#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>

#include "../Entities/Player.h"
#include "../UI/UIElement.h"
#include "../UI/Pages/MenuPage.h"

//Creates the default application window
SDL_Window * CreateWindow();

//Cleans up game resources
void CleanUp(SDL_Window* window);

int main(int argc, char* argv[]) {
	auto window = CreateWindow();
	auto windowSurface = SDL_GetWindowSurface(window);

	auto previousTicks = 0L;
	auto currentTicks = 0L;
	auto deltaTicks = 0.0;

	auto menuPage = * new MenuPage(window);
	menuPage.Run();

	/*Player player(0, 0, "mainCharacter.png");

	while (true) {
		currentTicks = SDL_GetTicks();
		printf("previousTicks: %ld\ncurrentTicks: %ld\n", previousTicks, currentTicks);
		deltaTicks = currentTicks - previousTicks;
		deltaTicks /= 1000;
		SDL_FillRect(windowSurface, NULL, 0x000000);
		SDL_BlitSurface(player.getModel(), &player.getModel()->clip_rect, windowSurface, &player.getBounds());
		player.setX(player.getX() + 10 * deltaTicks);
		SDL_UpdateWindowSurface(window);

		previousTicks = currentTicks;

		auto playerBounds = player.getBounds();
		playerBounds.x = player.getX();
		player.setBounds(playerBounds);
	}*/

	CleanUp(window);
	return 0;
}

SDL_Window * CreateWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);   // Initialize SDL2

	SDL_Window *window;        // Declare a pointer to an SDL_Window
							   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",         //    const char* title
		SDL_WINDOWPOS_UNDEFINED,  //    int x: initial x position
		SDL_WINDOWPOS_UNDEFINED,  //    int y: initial y position
		640,                      //    int w: width, in pixels
		480,                      //    int h: height, in pixels
		SDL_WINDOW_SHOWN          //    Uint32 flags: window options, see docs
		);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		std::cout << "Could not create window: " << SDL_GetError() << '\n';
		SDL_Quit();
		return nullptr;
	}

	return window;
}

void CleanUp(SDL_Window* window)
{
	SDL_DestroyWindow(window);

	// Clean up SDL2 and exit the program
	SDL_Quit();
}