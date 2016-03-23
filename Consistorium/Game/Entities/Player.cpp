#include "Player.h"

Player::Player(b2Vec2 position, char *modelName, float width, float height)
	:textureName_(modelName)
{
	width_ = width;
	height_ = height;
}

Player::~Player()
{
	delete[] textureName_;
	textureName_ = nullptr;
	body_ = nullptr;
}

void Player::setSpeed(float speed)
{
	speed_ = speed;
}

float Player::getSpeed()
{
	return speed_;
}

char* Player::getTextureName()
{
	return this->textureName_;
}

b2Vec2 Player::getPosition()
{
	return body_->GetPosition();
}

b2BodyDef Player::getBodyDef()
{
	return bodyDef_;
}

void Player::setBodyDef(b2BodyDef bodyDef)
{
	bodyDef_ = bodyDef;
}

b2Body* Player::getBody()
{
	return body_;
}

void Player::setBody(b2Body* body)
{
	body_ = body;
}

float Player::getWidth()
{
	return width_;
}

void Player::setWidth(float width)
{
	width_ = width;
}

float Player::getHeight()
{
	return height_;
}

void Player::setHeight(float height)
{
	height_ = height;
}
