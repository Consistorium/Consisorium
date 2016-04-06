#pragma once

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Block.h"

namespace Entities
{
	class EntityFactory
	{
	private:
		b2World* world_;
	public:
		EntityFactory(b2World* world);
		~EntityFactory();
		b2Body* createEntityBody(b2Vec2 position, b2BodyType bodyType, float width, float height);
		Player* createPlayer(b2Vec2 position, std::string modelName);
		Block* createBlock(b2Vec2 position, std::string modelName);
	};
}