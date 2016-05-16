#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <memory>

#include "./Menu/Menu.h"
#include "Game/Globals/Constants.h"

//Creates the default application window
SDL_Window * CreateWindow();

//Cleans up game resources
void CleanUp(SDL_Window* window);

int main(int argc, char* argv[]) {
	auto window = CreateWindow();

	Menu menuPage = * new Menu(window);
	menuPage.Run();

	CleanUp(window);
	return 0;
}

SDL_Window* CreateWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);   // Initialize SDL2

	SDL_Window *window;        // Declare a pointer to an SDL_Window
							   // Create an application window with the following settings:

	SDL_DisplayMode displayMode;
	SDL_GetDesktopDisplayMode(0, &displayMode);

	window = SDL_CreateWindow(
		"Consistorium",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Globals::SCREEN_WIDTH,
		Globals::SCREEN_HEIGHT,
		);

	// Check that the window was successfully made
	if (window == nullptr) {
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