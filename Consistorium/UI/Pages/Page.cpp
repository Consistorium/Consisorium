#include "Page.h"

Page::Page(SDL_Window * window)
	: window_(window)
{
	windowSurface_ = SDL_GetWindowSurface(window_);
}
