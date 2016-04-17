#pragma once

#include <Box2D\Box2D.h>

#include "../Globals/Constants.h"
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

		Player* createPlayer(b2Vec2 position, std::string modelName, float health = Globals::INITIAL_PLAYER_HEALTH);

		Block* createBlock(b2Vec2 position, std::string modelName);

		EntityComponents createEntityComponents(EntityDescriptor descriptor, int animationSpeed);

		Enemy* createSkeleton(
			b2Vec2 position,
			std::string modelName,
			float scanRange = Globals::SKELETON_SCAN_RANGE,
			float damage = Globals::SKELETON_DAMAGE,
			float range = Globals::SKELETON_RANGE,
			float haste = Globals::SKELETON_HASTE);

		Tree* createTree(b2Vec2 position, std::string modelName);
	};
}