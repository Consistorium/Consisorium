#pragma once

#include <Box2D\Box2D.h>

#include "../Globals/Constants.h"
#include "Player.h"
#include "Objects\Block.h"
#include "Enemies\Skeleton.h"
#include <GameEngine/IGraphicsRenderer.h>
#include "EntityDescriptor.h"
#include "EntityComponents.h"
#include "Objects\Tree.h"
#include <EntityManager.h>
#include <Bush.h>

namespace Entities
{
	class EntityFactory
	{
	private:
		EntityManager& entityManager_;
		std::vector<Enemy*>& permantentlyLivingEnemies_;
	public:
		EntityFactory(EntityManager& entityManager,
			std::vector<Enemy*>& permantentlyLivingEnemies);

		~EntityFactory();

		b2Body* createDynamicEntityBody(b2Vec2 position, float width, float height, float friction = 1);

		b2Body* createEntityBody(b2BodyType bodyType, b2Vec2 position, double width, double height);

		Player* createPlayer(b2Vec2 position, std::string modelName, float health = Globals::INITIAL_PLAYER_HEALTH);

		Block* createBlock(b2Vec2 position, std::string modelName);

		Bush* createBush(b2Vec2 position, std::string modelName);

		GameEntity* createFromName(b2Vec2 position, std::string name);

		GameEntity* createFromName(b2Vec2 position, std::string name, std::vector<std::vector<Entities::GameEntity*>>& cache, b2Vec2 indexes);

		EntityComponents createEntityComponents(EntityDescriptor descriptor, int animationSpeed);

		Enemy* createEnemy(
			b2Vec2 position,
			std::string modelName,
			std::string entityName,
			float scanRange = Globals::SKELETON_SCAN_RANGE,
			float damage = Globals::SKELETON_DAMAGE,
			float range = Globals::SKELETON_RANGE,
			float haste = Globals::SKELETON_HASTE);

		GameEntity* createFoliage(b2Vec2 position, std::string entityName, std::string modelName, int height, int width);
	};
}
