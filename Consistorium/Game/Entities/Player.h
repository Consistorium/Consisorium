#pragma once

#include <SDL\SDL.h>
#include "GameEntity.h"

class Player : public GameEntity
{
	char *textureName_;
public:
	Player(b2Vec2 position, char *modelName);
	~Player();

	void init(SDL_Renderer *renderer);

	char* getTextureName() override;

	b2Vec2 getPosition() override;

	b2BodyDef getBodyDef() override;

	void setBodyDef(b2BodyDef bodyDef) override;

	b2Body* getBody() override;

	void setBody(b2Body* body) override;
};

