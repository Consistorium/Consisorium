#include "Player.h"

const float PLAYER_SPEED = 1000;

Player::Player(b2Vec2 position, std::string defaultAnimation, float width, float height, float jumpPower)
	: textureName_(this->getAnimationsFolder() + "/" + defaultAnimation + "001.png"),
	animationManager_(this, defaultAnimation)
{
	width_ = width;
	height_ = height;
	jumpPower_ = jumpPower;
	speed_ = 0;
}

Player::~Player()
{
	body_ = nullptr;
}

void Player::setFrameTexture(std::string path) 
{
	this->textureName_ = path;
}

b2Vec2 Player::getScale()
{
	b2Vec2 vec(0.2, 0.2);
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

std::string Player::getAnimationsFolder()
{
	return "Models/Game/Player";
}

double Player::getAnimationSpeed()
{
	return 45; // ms
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

float Player::getJumpPower()
{
	return jumpPower_;
}

void Player::setJumpPower(float power)
{
	jumpPower_ = power;
}

float Player::getAccelerationImpulse()
{
	float xVelocity = body_->GetLinearVelocity().x;

	return (PLAYER_MAX_SPEED - (xVelocity * xDirection_)) * xDirection_;
}

void Player::setXDirection(int direction)
{
	xDirection_ = direction;
}