#include "GameEntity.h"

namespace Entities
{
	GameEntity::GameEntity(GameEngine::RenderComponent& rc)
		: body_(rc.getBody()),
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

	b2Body* GameEntity::getBody()
	{
		return renderComponent_.getBody();
	}

	GameEngine::IRenderable* GameEntity::getRenderableComponent()
	{
		return &renderComponent_;
	}

	b2Vec2 GameEntity::getPosition()
	{
		return body_->GetPosition();
	}

	b2Vec2 GameEntity::getSize()
	{
		return renderComponent_.getSize();
	}
}