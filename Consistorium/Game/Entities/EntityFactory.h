#pragma once

#include <Box2D\Box2D.h>

#include "GameEntity.h"

class EntityFactory
{
private:
	b2World* world_;
public:
	EntityFactory(b2World* world);
	~EntityFactory();
	GameEntity* createPlayer(b2Vec2 position, char* modelName);
};