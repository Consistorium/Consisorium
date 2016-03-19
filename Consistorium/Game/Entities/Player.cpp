#include "Player.h"

const float PLAYER_SPEED = 1000;

Player::Player(GameEngine::Vector2D position, char *modelName) 
	: IMoveable(PLAYER_SPEED),
	IPositionable(position),
	textureName_(modelName)
{
}

Player::~Player()
{
	delete[] textureName_;
	textureName_ = NULL;
}

char* Player::getTextureName()
{
	return this->textureName_;
}

GameEngine::Vector2D Player::getScreenPosition()
{
	return this->getPosition();
}