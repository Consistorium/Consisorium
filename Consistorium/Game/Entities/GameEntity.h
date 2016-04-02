#pragma once

#include <string>
#include <memory>
#include <SDL/SDL.h>
#include <Box2D\Box2D.h>
#include <RenderComponent.h>
#include <IAnimateable.h>
#include <AnimationComponent.h>
#include <AnimationManager.h>

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
		
		virtual void setBody(b2Body* body);
	};
}