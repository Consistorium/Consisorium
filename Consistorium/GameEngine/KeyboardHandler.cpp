#include "KeyboardHandler.h"

enum KeyStates {
	PRESSED = true,
	RELEASED = false
};

KeyboardHandler::KeyboardHandler()
{
}

void KeyboardHandler::handleKeyPress(SDL_Event e, SDL_Keycode key) {
	if (e.type == SDL_KEYDOWN)
	{
		keyboard_[key] = PRESSED;
	}
	else if (e.type == SDL_KEYUP)
	{
		keyboard_[key] = RELEASED;
	}
}

bool KeyboardHandler::isPressed(SDL_Keycode key)
{
	return keyboard_[key] == PRESSED;
}

SDL_Keycode KeyboardHandler::isNumberPressed()
{
	for (SDL_Keycode i = SDLK_0; i <= SDLK_9; i++)
	{
		std::map<SDL_Keycode, bool>::iterator it = keyboard_.find(i);
		if (it != keyboard_.end() && it->second)
		{
			return i;
		}
	}

	return 0;
}

KeyboardHandler::~KeyboardHandler()
{
}