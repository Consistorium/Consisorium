#include "Player.h"

const float PLAYER_SPEED = 20;

Player::Player(float beginX, float beginY, const char *modelName, bool anchorState) 
	: IMoveable(PLAYER_SPEED),
	IPositionable(beginX, beginY),
	IVisible(modelName, beginX, beginY),
	Entity(anchorState)
{
}

Player::~Player()
{
}