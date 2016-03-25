#pragma once

#include <SDL\SDL.h>
#include "GameEntity.h"

class Player : public GameEntity
{
private:
	char *textureName_;
	const float PLAYER_MAX_SPEED = 0.3;
	int xDirection_;
public:
	//TODO:apply builder pattern
	Player(b2Vec2 position, char *modelName, float width, float height, float jumpPower);
	~Player();

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

	float getJumpPower() override;

	void setJumpPower(float power) override;

	void setXDirection(int direction) override;

	float getAccelerationImpulse() override;
};

