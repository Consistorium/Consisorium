#pragma once

#include <memory>
#include <Box2D\Box2D.h>
#include <IRenderable.h>
#include <TextureManager.h>
#include <Interfaces/IPositionable.h>
#include <Interfaces/IMoveable.h>
#include <Interfaces/IVisible.h>

#include "Player.h"
#include "Entity.h"

class Player :
	public Entity,
	public IMoveable,
	public IPositionable,
	public GameEngine::IRenderable
{
private:
	char *textureName_;
	b2Body* body_;
	b2BodyDef bodyDef_;
public:
	Player(b2Vec2 position, char *modelName);
	~Player();

	void init(SDL_Renderer *renderer);

	char* getTextureName() override;

	b2Vec2 getScreenPosition() override;

	void setPosition(b2Vec2 position) override;

	b2BodyDef getBodyDef();

	void setBodyDef(b2BodyDef bodyDef);

	b2Body* getBody();

	void setBody(b2Body* body);
};

