#include "PlayerMovementManager.h"
#include <iostream>

PlayerMovementManager::PlayerMovementManager()
{
}

PlayerMovementManager::~PlayerMovementManager()
{
}

void moveCharacterLeft(Player* player, float deltaTicks)
{
	player->setX(player->getX() - player->getSpeed() + player->getSpeed() * deltaTicks);
}

void moveCharacterRight(Player* player, float deltaTicks)
{
	player->setX(player->getX() + player->getSpeed() + player->getSpeed() * deltaTicks);
}

void PlayerMovementManager::handleMovement(SDL_Keycode key, Player* player, float deltaTicks)
{
	//TODO: falling
	switch (key)
	{
	case SDLK_LEFT:
		moveCharacterLeft(player, deltaTicks);
		break;
	case SDLK_RIGHT:
		moveCharacterRight(player, deltaTicks);
		break;
	default:
		break;
	}
}