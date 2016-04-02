#include "GameEntity.h"

namespace Entities
{
	GameEntity::GameEntity(GameEngine::RenderComponent& rc)
		: body_(nullptr),
		renderComponent_(*rc.getTextureName(), rc.getScale(), rc.getPosition())
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
		return body_;
	}

	void GameEntity::setBody(b2Body* body)
	{
		body_ = body;
	}

	GameEngine::IRenderable* GameEntity::getRenderableComponent()
	{
		return &renderComponent_;
	}

}