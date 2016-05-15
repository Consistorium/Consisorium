#include <vector>
#include <Game\Globals\Constants.h>

#include "Capsule.h"
#include "Box.h"
#include "EntityTypes.h"

#include "EntityFactory.h"

namespace Entities
{
	const float PLAYER_JUMP_POWER = 5.0;
	const int ENTITY_Z_INDEX = 0;
	const int TREE_Z_INDEX = -1;

	EntityFactory::EntityFactory(EntityManager& entityManager, std::vector<Enemy*>& permantentlyLivingEnemies)
		: entityManager_(entityManager),
		permantentlyLivingEnemies_(permantentlyLivingEnemies)
	{
	}

	b2Body* EntityFactory::createDynamicEntityBody(b2Vec2 position, float width, float height, float friction) {
		b2Body* body = Bodies::Capsule::create(entityManager_.getWorld(), position, width, height);
		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetFriction(friction);
			fixture->SetDensity(1.0);
			fixture = fixture->GetNext();
		}

		return body;
	}

	EntityComponents EntityFactory::createEntityComponents(EntityDescriptor descriptor, int animationSpeed)
	{
		b2Body* body = createEntityBody(descriptor.bodyType, descriptor.position, descriptor.width, descriptor.height);

		GameEngine::RenderComponent* rc = new GameEngine::RenderComponent(
			Globals::MODELS_LOCATION + descriptor.entityName + "/" + descriptor.modelName + "__001.png",
			b2Vec2(descriptor.width * Globals::PIXELS_PER_METER, descriptor.height * Globals::PIXELS_PER_METER),
			nullptr,
			false);

		GameEngine::AnimationComponent* ac = new GameEngine::AnimationComponent(
			Globals::MODELS_LOCATION + descriptor.entityName,
			descriptor.animation,
			animationSpeed,
			rc->getTextureName());

		EntityComponents components;
		components.animationComponent = ac;
		components.renderComponent = rc;
		components.body = body;

		return components;
	}

	b2Body* EntityFactory::createEntityBody(b2BodyType bodyType, b2Vec2 position, double width, double height)
	{
		switch (bodyType)
		{
		case b2_staticBody:
			return Bodies::Box::create(entityManager_.getWorld(), position, width, height);
		case b2_dynamicBody:
			return createDynamicEntityBody(position, width, height);
		}
	}

	GameEntity* EntityFactory::createFromName(b2Vec2 position, std::string name)
	{
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		GameEntity *result = nullptr;
		if (name.compare("grass") == 0)
		{
			result = createBlock(position, "Grass");
			result->setZIndex(ENTITY_Z_INDEX)
				->setType((int)EntityTypes::Grass);
		}
		else if (name.compare("ground") == 0) 
		{
			result = createBlock(position, "Ground");
			result->setZIndex(ENTITY_Z_INDEX)
				->setType((int)EntityTypes::Rock);
		} 
		else if (name.compare("skeleton") == 0)
		{
			position.x /= Globals::PIXELS_PER_METER;
			position.y /= Globals::PIXELS_PER_METER;
			result = createEnemy(position, "Skeleton", "Idle");
			permantentlyLivingEnemies_.push_back(static_cast<Enemy*>(result));
		}
		else if (name.compare("pinetree") == 0)
		{
			result = createFoliage(position, "Tree", "Pine", Globals::TREE_HEIGHT, Globals::TREE_WIDTH);
			result->setType((int)EntityTypes::Pine);
		}
		if (name.compare("purgatory") == 0)
		{
			result = createBlock(position, "Purgatory");
			result->setType((int)EntityTypes::PurgatoryBlock);
		}
		else if (name.compare("bush") == 0)
		{
			result = createFoliage(position, "Bush", "Bush", Globals::BUSH_HEIGHT, Globals::BUSH_WIDTH);
			result->setType((int)EntityTypes::Bush);
		}
		else if (name.compare("ruin") == 0)
		{
			result = createBlock(position, "Ruin");
			result->setType((int)EntityTypes::Ruin);
		}
		else if (name.compare("hell") == 0)
		{
			result = createBlock(position, "Hell");
			result->setType((int)EntityTypes::Hell);
		}

		return result;
	}

	GameEntity* EntityFactory::createFromName(b2Vec2 position, std::string name, std::vector<std::vector<Entities::GameEntity*>>& cache, b2Vec2 indexes)
	{
		GameEntity *result = nullptr;

		if (name.compare("delete") == 0)
		{
			if (indexes.y < 0 || indexes.y >= cache.size() ||
				indexes.x < 0 || indexes.x >= cache[indexes.y].size()) 
			{
				return nullptr;
			}
			result = cache[indexes.y][indexes.x];
			if (result != nullptr)
			{
				entityManager_.removeFromWorld(result);
				cache[indexes.y][indexes.x] = nullptr;
			}

			return result;
		}

		return createFromName(position, name);
	}

	Player* EntityFactory::createPlayer(b2Vec2 position, std::string modelName, float health)
	{
		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName("Player")
			.withModelName(modelName)
			.withPosition(position)
			.withBodyType(b2_dynamicBody)
			.withWidth(Globals::DEFAULT_ENTITY_WIDTH / Globals::PIXELS_PER_METER)
			.withHeight(Globals::DEFAULT_ENTITY_HEIGHT / Globals::PIXELS_PER_METER)
			.create();

		EntityComponents components = createEntityComponents(descriptor, 40);

		components.body->SetUserData((void*)EntityTypes::Player);

		Player* player = new Player(components.body, components.renderComponent, components.animationComponent, EventManager::get());
		player->setJumpPower(0.2f)
			->setMaxSpeed(10.0f)
			->setMaxHealth(health)
			->setHealth(health)
			->setZIndex(ENTITY_Z_INDEX)
			->setType((int)EntityTypes::Player);

		components.renderComponent->forEntity(player);
		entityManager_.addToWorld(player);
		return player;
	}

	Block* EntityFactory::createBlock(b2Vec2 position, std::string modelName)
	{
		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName("Block")
			.withModelName(modelName)
			.withPosition(position)
			.withBodyType(b2_staticBody)
			.withWidth(Globals::BLOCK_WIDTH / Globals::PIXELS_PER_METER)
			.withHeight(Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER)
			.create();

		EntityComponents components = createEntityComponents(descriptor, 80);
		components.body->SetUserData((void*)EntityTypes::Block);
		b2Fixture* fixture = components.body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetUserData((void*)EntityTypes::Block);
			fixture->SetFriction(1.0);
			fixture = fixture->GetNext();
		}

		Block* block = new Block(components.body, components.renderComponent);
		block->setZIndex(ENTITY_Z_INDEX)
			->setType((int)EntityTypes::Block);

		components.renderComponent->forEntity(block);
		entityManager_.addToWorld(block);
		return block;
	}

	Enemy* EntityFactory::createEnemy(b2Vec2 position, std::string modelName, std::string entityName, float scanRange, float damage, float range, float haste)
	{
		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName(entityName)
			.withModelName(modelName)
			.withPosition(position)
			.withBodyType(b2_dynamicBody)
			.withWidth(Globals::DEFAULT_ENTITY_WIDTH / Globals::PIXELS_PER_METER)
			.withHeight(Globals::DEFAULT_ENTITY_HEIGHT / Globals::PIXELS_PER_METER)
			.create();

		EntityComponents components = createEntityComponents(descriptor, 80);
		Enemy* skeleton = new Skeleton(components.body, components.renderComponent, components.animationComponent);
		skeleton->setJumpPower(Globals::ENTITY_JUMP_POWER)
			->setScanRange(scanRange)
			->setDamage(damage)
			->setRange(range)
			->setHaste(haste)
			->setZIndex(ENTITY_Z_INDEX)
			->setType((int)EntityTypes::Skeleton);

		components.renderComponent->forEntity(skeleton);
		entityManager_.addToWorld(skeleton);
		return skeleton;
	}

	GameEntity* EntityFactory::createFoliage(b2Vec2 position, std::string entityName, std::string modelName, int height, int width)
	{
		position.y += height / 2;
		position.y -= Globals::BLOCK_HEIGHT / 2;
		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName(entityName)
			.withModelName(modelName)
			.withPosition(position)
			.withBodyType(b2_staticBody)
			.withWidth(width / Globals::PIXELS_PER_METER)
			.withHeight(height / Globals::PIXELS_PER_METER)
			.create();

		EntityComponents components = createEntityComponents(descriptor, 80);
		Tree* tree = new Tree(components.body, components.renderComponent);
		tree->setZIndex(TREE_Z_INDEX)
			->setType((int)EntityTypes::Pine);
		components.renderComponent->forEntity(tree);
		entityManager_.addToWorld(tree);
		tree->getBody()->GetFixtureList()->SetSensor(true);

		return tree;
	}

	EntityFactory::~EntityFactory()
	{
	}
}
