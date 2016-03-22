#include "Player.h"

Player::Player(b2Vec2 position, char *modelName)
	:textureName_(modelName)
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