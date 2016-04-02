#include "Window.h"

namespace GameEngineUI
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