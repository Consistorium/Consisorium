#include "Window.h"

Window::Window(SDL_Window * window)
	: window_(window)
{
	windowSurface_ = SDL_GetWindowSurface(window_);
}