#pragma once

#include "SDL.h"
#include "../Entities/Player.h"

class PlayerMovementManager
{
public:
	PlayerMovementManager();
	~PlayerMovementManager();

	void handleMovement(SDL_Keycode key, Player* player, float deltaTicks);
};