#pragma once

#include <string>
#include <memory>
#include <SDL/SDL.h>
#include <Box2D\Box2D.h>
#include <IRenderable.h>
#include <IAnimateable.h>
#include <AnimationManager.h>

namespace Entities
{
	class GameEntity : 
		public GameEngine::IRenderable,
		public GameEngine::IAnimateable
	{
	protected:
		b2Body* body_;
		b2BodyDef bodyDef_;
		float width_;
		float height_;
		std::string textureName_;
		int animationSpeed_;
		GameEngine::AnimationManager animationManager_;
		std::string animationsFolder_;
	public:
		GameEntity(std::string textureName, float width, float height);
		virtual b2BodyDef getBodyDef();

		virtual b2Body* getBody();

		virtual void setBody(b2Body* body);

		virtual float getWidth();

		virtual void setWidth(float width);

		virtual float getHeight() override;

		virtual void setHeight(float height);

		virtual std::string getTextureName();

		virtual b2Vec2 getPosition();

		virtual b2Vec2 getScale();

		virtual double getAnimationSpeed();

		virtual void setFrameTexture(std::string path);

		virtual std::string getAnimationsFolder();

		virtual void setAnimationsFolder(std::string animationsFolder);

		~GameEntity();
	};
}