#include "GameEntity.h"

namespace Entities
{
	GameEntity::GameEntity(b2Body* body, GameEngine::RenderComponent* rc)
		: body_(body),
		renderComponent_(rc)
	{
	}


	GameEntity::~GameEntity()
	{
		body_ = nullptr;
	}

	b2BodyDef GameEntity::getBodyDef()
	{
		return bodyDef_;
	}

	GameEngine::IRenderable* GameEntity::getRenderableComponent()
	{
		return renderComponent_;
	}

	b2Vec2 GameEntity::getPosition()
	{
		return body_->GetPosition();
	}

	int GameEntity::getUserData()
	{
		return (int)body_->GetUserData();
	}

	b2Vec2 GameEntity::getSize()
	{
		return renderComponent_->getSize();
	}

	float GameEntity::getHealth()
	{
		return health_;
	}

	float GameEntity::getMaxHealth()
	{
		return maxHealth_;
	}

	b2Body* GameEntity::getBody()
	{
		return body_;
	}

	GameEntity* GameEntity::setHealth(float value)
	{
		health_ = value;
		return this;
	}

	GameEntity* GameEntity::setMaxHealth(float value)
	{
		maxHealth_ = value;
		return this;
	}
}