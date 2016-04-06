#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <memory>

#include "./Menu/Menu.h"

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
	window = SDL_CreateWindow(
		"An SDL2 window",         //    const char* title
		SDL_WINDOWPOS_UNDEFINED,  //    int x: initial x position
		SDL_WINDOWPOS_UNDEFINED,  //    int y: initial y position
		1280,                      //    int w: width, in pixels
		768,                      //    int h: height, in pixels
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