#pragma once

#include <map>
#include <SDL\SDL.h>

class KeyboardHandler
{
private:
	std::map<SDL_Keycode, bool> keyboard_;
public:
	KeyboardHandler();

	void handleKeyPress(SDL_Event e, SDL_Keycode key);

	bool isPressed(SDL_Keycode key);

	SDL_Keycode isNumberPressed();

	~KeyboardHandler();
};