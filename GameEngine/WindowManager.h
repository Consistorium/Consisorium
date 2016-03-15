#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "ErrorManager.h"

namespace GameEngine 
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		void create(char *name, int width, int height);

		void swapBuffers();

		int getWidth() { return this->windowWidth_; }
		int getHeight() { return this->windowHeight_; }

	private:
		SDL_Window *window_;
		int windowWidth_;
		int windowHeight_;
	};
}