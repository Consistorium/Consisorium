#pragma once

#include <SDL/SDL.h>

namespace GameEngine
{
	class Window
	{
	private:
		virtual void Init() = 0;
	protected:
		SDL_Window* window_;
		SDL_Surface* windowSurface_;
	public:
		Window(SDL_Window* window);

		virtual ~Window();

		virtual void Run() = 0;
	};
}