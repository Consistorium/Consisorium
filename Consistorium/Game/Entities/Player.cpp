#include "Player.h"

const float PLAYER_SPEED = 1000;

Player::Player(b2Vec2 position, char *modelName)
	: IMoveable(PLAYER_SPEED),
	IPositionable(position),
	textureName_(modelName)
{
}

Player::~Player()
{
	delete[] textureName_;
	textureName_ = nullptr;
	body_ = nullptr;
}

char* Player::getTextureName()
{
	return this->textureName_;
}

b2Vec2 Player::getScreenPosition()
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

void Player::setPosition(b2Vec2 position)
{
}