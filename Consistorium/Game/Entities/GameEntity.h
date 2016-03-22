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
public:
	virtual ~GameEntity() { };

	virtual b2BodyDef getBodyDef() = 0;

	virtual void setBodyDef(b2BodyDef bodyDef) = 0;

	virtual b2Body* getBody() = 0;

	virtual void setBody(b2Body* body) = 0;
};