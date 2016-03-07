#include "Player.h"

Player::Player(float beginX, float beginY, const char *modelName) 
	: IMoveable(PLAYER_SPEED),
	IPositionable(beginX, beginY),
	IVisible(modelName, beginX, beginY)
{
}

Player::~Player()
{
}
