#pragma once

#include <Box2D\Box2D.h>
#include "RenderComponent.h"

namespace Entities
{
	class GameEntity : public Entity
	{
	protected:
		b2Body* body_;
		GameEngine::RenderComponent* renderComponent_;
		b2BodyDef bodyDef_;
		float health_;
		float maxHealth_;
		int zIndex_;
	public:
		GameEntity(b2Body* body, GameEngine::RenderComponent* rc);

		virtual ~GameEntity();

		GameEngine::IRenderable* getRenderableComponent();

		virtual b2BodyDef getBodyDef();

		virtual b2Body* getBody();

		virtual b2Vec2 getPosition();

		virtual b2Vec2 getSize();

		virtual int getUserData();

		virtual float getHealth();

		virtual float getMaxHealth();

		virtual GameEntity* setHealth(float value);

		virtual GameEntity* setMaxHealth(float value);

		GameEntity* setZIndex(int index);

		int getZIndex();
	};
}
