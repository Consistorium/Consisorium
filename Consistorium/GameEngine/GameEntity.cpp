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

	void GameEntity::setHealth(float health)
	{
		if (health >= 0)
		{
			health_ = health;
		}
	}

	float GameEntity::getHealth()
	{
		return health_;
	}

	float GameEntity::getMaxHealth()
	{
		return maxHealth_;
	}

	void GameEntity::setMaxHealth(float value)
	{
		if (value > 0)
		{
			maxHealth_ = 0;
		}
	}

	b2Body* GameEntity::getBody()
	{
		return body_;
	}
}