#include "GameEntity.h"

namespace Entities
{
	GameEntity::GameEntity(std::string defaultAnimation, float width, float height)
		: width_(width),
		height_(height),
		animationManager_(this, defaultAnimation)
	{
	}


	GameEntity::~GameEntity()
	{
		textureName_ = nullptr;
		body_ = nullptr;
	}

	std::string GameEntity::getTextureName()
	{
		this->animationManager_.updateAnimation();
		return this->textureName_;
	}

	b2Vec2 GameEntity::getPosition()
	{
		return body_->GetPosition();
	}

	b2BodyDef GameEntity::getBodyDef()
	{
		return bodyDef_;
	}

	b2Body* GameEntity::getBody()
	{
		return body_;
	}

	void GameEntity::setBody(b2Body* body)
	{
		body_ = body;
	}

	float GameEntity::getWidth()
	{
		return width_;
	}

	void GameEntity::setWidth(float width)
	{
		width_ = width;
	}

	float GameEntity::getHeight()
	{
		return height_;
	}

	void GameEntity::setHeight(float height)
	{
		height_ = height;
	}


	void GameEntity::setFrameTexture(std::string path)
	{
		this->textureName_ = path;
	}

	void GameEntity::setAnimationsFolder(std::string animationsFolder)
	{
		animationsFolder_ = animationsFolder;
	}

	std::string GameEntity::getAnimationsFolder()
	{
		return animationsFolder_;
	}

	double GameEntity::getAnimationSpeed()
	{
		return animationSpeed_; // ms
	}

	b2Vec2 GameEntity::getScale()
	{
		b2Vec2 vec(1, 1);
		return vec;
	}
}