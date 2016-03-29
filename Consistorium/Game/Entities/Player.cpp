#include "Player.h"

const float PLAYER_SPEED = 1000;

Player::Player(GameEngine::Vector2D position, std::string defaultAnimation)
	: IMoveable(PLAYER_SPEED),
	IPositionable(position),
	textureName_(this->getAnimationsFolder() + "/" + defaultAnimation + "001.png"),
	animationManager_(this, defaultAnimation)
{
}

Player::~Player()
{
}

void Player::setFrameTexture(std::string path) 
{
	this->textureName_ = path;
}

GameEngine::Vector2D Player::getScale()
{
	GameEngine::Vector2D vec(0.2, 0.2);
	return vec;
}

void Player::die()
{
	this->animationManager_.setAnimation("Run", false);
}

std::string Player::getTextureName() 
{
	this->animationManager_.updateAnimation();
	return this->textureName_;
}

GameEngine::Vector2D Player::getScreenPosition()
{
	return this->getPosition();
}

std::string Player::getAnimationsFolder()
{
	return "Models/Game/Player";
}

double Player::getAnimationSpeed()
{
	return 45; // ms
}