#pragma once

#include <SDL/SDL.h>
#include <memory>
#include <Box2D\Box2D.h>
#include <IRenderable.h>

class GameEntity : public GameEngine::IRenderable
{
protected:
	b2Body* body_;
	b2BodyDef bodyDef_;
	float speed_;
	float width_;
	float height_;
public:
	virtual void setSpeed(float speed) = 0;

	virtual float getSpeed() = 0;	

	virtual b2BodyDef getBodyDef() = 0;

	virtual void setBodyDef(b2BodyDef bodyDef) = 0;

	virtual b2Body* getBody() = 0;

	virtual void setBody(b2Body* body) = 0;

	virtual float getWidth() = 0;

	virtual void setWidth(float width) = 0;

	virtual float getHeight() = 0;

	virtual void setHeight(float height) = 0;

	virtual ~GameEntity() { };
};