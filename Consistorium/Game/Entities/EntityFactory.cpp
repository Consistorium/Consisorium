#include <vector>
#include <Game\Globals\Constants.h>

#include "Capsule.h"
#include "EntityIndexesEnum.h"

#include "EntityFactory.h"

namespace Entities
{
	const float PLAYER_JUMP_POWER = 5.0;

	EntityFactory::EntityFactory(EntityManager& entityManager)
		: entityManager_(entityManager)
	{
	}

	b2Body* EntityFactory::createDynamicEntityBody(b2Vec2 position, float width, float height, float friction) {
		b2Body* body = Capsule::create(entityManager_.getWorld(), position, width, height);
		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetFriction(friction);
			fixture->SetDensity(1.0);
			fixture = fixture->GetNext();
		}

		//add foot sensor fixture
		float sensorDim = 0.1;
		b2Vec2 sensorCentre(0, -height / 2 - sensorDim / 2);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(sensorDim, sensorDim, sensorCentre, 0);

		b2FixtureDef SensorFixtureDef;
		SensorFixtureDef.shape = &polygonShape;
		SensorFixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&SensorFixtureDef);
		footSensorFixture->SetUserData((void*)EntityIndexes::FootSensor);

		return body;
	}

	b2Body* EntityFactory::createStaticEntityBody(b2Vec2 position, float width, float height)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(position.x / Globals::PIXELS_PER_METER, position.y / Globals::PIXELS_PER_METER);
		bodyDef.fixedRotation = true;
		b2Body* body = entityManager_.getWorld()->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(width / 2.0f, height / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		body->CreateFixture(&fixtureDef);

		return body;
	}

	EntityComponents EntityFactory::createEntityComponents(EntityDescriptor descriptor, int animationSpeed)
	{
		b2Body* body = createEntityBody(descriptor.bodyType, descriptor.position, descriptor.width, descriptor.height);

		GameEngine::RenderComponent* rc = new GameEngine::RenderComponent(
			Globals::MODELS_LOCATION + descriptor.entityName + "/" + descriptor.modelName + "__001.png",
			b2Vec2(descriptor.width * Globals::PIXELS_PER_METER, descriptor.height * Globals::PIXELS_PER_METER));

		GameEngine::AnimationComponent* ac = new GameEngine::AnimationComponent(
			Globals::MODELS_LOCATION + descriptor.entityName,
			descriptor.animation,
			animationSpeed, //default animation speed
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
			return createStaticEntityBody(position, width, height);
		case b2_dynamicBody:
			return createDynamicEntityBody(position, width, height);
		}
	}

	GameEntity* EntityFactory::createFromName(b2Vec2 position, std::string name)
	{
		GameEntity *result = nullptr;
		if (name.compare("grass") == 0)
		{
			result = createBlock(position, "Grass");
		}
		else if (name.compare("ground") == 0) 
		{
			result = createBlock(position, "Ground");
		}
		else if (name.compare("pineTree") == 0)
		{
			result = createTree(position, "Pine");
			result->getBody()->GetFixtureList()->SetSensor(true);
		}
		else if (name.compare("delete") == 0)
		{
			int index = 0;
			result = entityManager_.getClickedEntity(position, &index);
			if (result != nullptr) 
			{
				entityManager_.removeFromWorld(index);
			}
		}

		return result;
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

		components.body->SetUserData((void*)EntityIndexes::Player);

		Player* player = new Player(components.body, components.renderComponent, components.animationComponent);
		player->setJumpPower(0.2f)
			->setMaxSpeed(10.0f)
			->setMaxHealth(health)
			->setHealth(health);

		entityManager_.addToWorld(player);
		components.renderComponent->forEntity(player);
		return player;
	}

	Block* EntityFactory::createBlock(b2Vec2 position, std::string modelName)
	{
		position.y += Globals::BLOCK_HEIGHT / 2;
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
		components.body->SetUserData((void*)EntityIndexes::Block);
		b2Fixture* fixture = components.body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetUserData((void*)EntityIndexes::Block);
			fixture->SetFriction(1.0);
			fixture = fixture->GetNext();
		}

		Block* block = new Block(components.body, components.renderComponent);


		entityManager_.addToWorld(block);
		components.renderComponent->forEntity(block);
		return block;
	}

	Enemy* EntityFactory::createSkeleton(b2Vec2 position, std::string modelName, float scanRange, float damage, float range, float haste)
	{
		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName("Skeleton")
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
			->setHaste(haste);

		entityManager_.addToWorld(skeleton);
		components.renderComponent->forEntity(skeleton);
		return skeleton;
	}

	Tree* EntityFactory::createTree(b2Vec2 position, std::string modelName)
	{
		position.y += Globals::TREE_HEIGHT / 2;

		EntityDescriptor descriptor = EntityDescriptor()
			.withAnimation(modelName)
			.withEntityName("Tree")
			.withModelName(modelName)
			.withPosition(position)
			.withBodyType(b2_staticBody)
			.withWidth(Globals::TREE_WIDTH / Globals::PIXELS_PER_METER)
			.withHeight(Globals::TREE_HEIGHT / Globals::PIXELS_PER_METER)
			.create();

		EntityComponents components = createEntityComponents(descriptor, 80);
		Tree* tree = new Tree(components.body, components.renderComponent);

		entityManager_.addToWorld(tree);
		components.renderComponent->forEntity(tree);
		return tree;
	}

	EntityFactory::~EntityFactory()
	{
	}
}
