#pragma once

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Block.h"
#include "Enemies\Skeleton.h"
#include "EntityIndexesEnum.h"
#include "EntityDescriptor.h"
#include "EntityComponents.h"
#include "Tree.h"

namespace Entities
{
	class EntityFactory
	{
	private:
		b2World* world_;
	public:
		EntityFactory(b2World* world);

		~EntityFactory();

		b2Body* createStaticEntityBody(b2Vec2 position, float width, float height);

		b2Body* createDynamicEntityBody(b2Vec2 position, float width, float height);

		Player* createPlayer(b2Vec2 position, std::string modelName);

		Block* createBlock(b2Vec2 position, std::string modelName);

		EntityComponents createEntityComponents(EntityDescriptor descriptor);

		Skeleton* createSkeleton(b2Vec2 position, std::string modelName);

		Tree* createTree(b2Vec2 position, std::string modelName);
	};
}