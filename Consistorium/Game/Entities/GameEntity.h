#pragma once

#include <Box2D\Box2D.h>
#include <RenderComponent.h>

namespace Entities
{
	class GameEntity
	{
	protected:
		b2Body* body_;
		GameEngine::RenderComponent renderComponent_;
		b2BodyDef bodyDef_;
	public:
		GameEntity(GameEngine::RenderComponent& renderComponent);

		virtual ~GameEntity();

		GameEngine::IRenderable* getRenderableComponent();

		virtual b2BodyDef getBodyDef();

		virtual b2Body* getBody();
	};
}