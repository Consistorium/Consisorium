#pragma once

#include <SDL/SDL.h>
#include <memory>
#include <Box2D\Box2D.h>
#include <IRenderable.h>
#include <IAnimateable.h>
class GameEntity : 
	public GameEngine::IRenderable,
	public GameEngine::IAnimateable
{
protected:
	b2Body* body_;
	b2BodyDef bodyDef_;
	float speed_;
	float width_;
	float height_;
	float jumpPower_;
public:
	virtual b2BodyDef getBodyDef() = 0;

	virtual void setBodyDef(b2BodyDef bodyDef) = 0;

	virtual b2Body* getBody() = 0;

	virtual void setBody(b2Body* body) = 0;

	virtual float getWidth() = 0;

	virtual void setWidth(float width) = 0;

	virtual float getHeight() = 0;

	virtual void setHeight(float height) = 0;

	virtual ~GameEntity() { };

	virtual float getJumpPower() = 0;

	virtual void setJumpPower(float power) = 0;

	virtual float getAccelerationImpulse() = 0;

	virtual void setXDirection(int direction) = 0;
};