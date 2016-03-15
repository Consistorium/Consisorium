#include "WindowManager.h"

namespace GameEngine {
	WindowManager::WindowManager()
	{
	}

	WindowManager::~WindowManager()
	{
	}

	void WindowManager::create(char *name, int width, int height)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		// TODO: Inject window mode flags as parameters.

		window_ = SDL_CreateWindow(name, 0, 0, width, height, flags);

		if (window_ == nullptr)
		{
			fatalError("Could not open SDL Window!");
		}

		windowHeight_ = height;
		windowWidth_ = width;

		SDL_GLContext glContext = SDL_GL_CreateContext(window_);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}
		std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WindowManager::swapBuffers()
	{
		SDL_GL_SwapWindow(window_);
	}
}
