#include "GameEntity.h"

namespace Entities
{
	GameEntity::GameEntity(GameEngine::RenderComponent& rc)
		: body_(rc.getBody()),
		renderComponent_(*rc.getTextureName(), rc.getScale(), body_)
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

}