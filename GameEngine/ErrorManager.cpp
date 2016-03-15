#include "ErrorManager.h"

namespace GameEngine 
{
	void throwError(char *message)
	{
		std::cerr << message << std::endl;
		SDL_Quit();
		exit(1);
	}
}
