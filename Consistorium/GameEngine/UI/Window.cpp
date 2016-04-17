#include "Window.h"

namespace GameEngine
{
	Window::Window(SDL_Window * window)
		: window_(window)
	{
		windowSurface_ = SDL_GetWindowSurface(window_);
	}

	Window::~Window()
	{
	}
}