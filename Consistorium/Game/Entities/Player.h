#pragma once

#include <SDL\SDL.h>
#include "GameEntity.h"

class Player : public GameEntity
{
private:
	char *textureName_;
	
public:
	Player(b2Vec2 position, char *modelName, float width, float height);
	~Player();

	void setSpeed(float speed) override;

	float getSpeed() override;

	void init(SDL_Renderer *renderer);

	char* getTextureName() override;

	b2Vec2 getPosition() override;

	b2BodyDef getBodyDef() override;

	void setBodyDef(b2BodyDef bodyDef) override;

	b2Body* getBody() override;

	void setBody(b2Body* body) override;

	float getWidth() override;

	void setWidth(float width) override;

	float getHeight() override;

	void setHeight(float height) override;
};

