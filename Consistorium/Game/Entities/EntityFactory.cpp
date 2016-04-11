#include <vector>
#include <EngineConstants.h>
#include <Game\Globals\Constants.h>

#include "Capsule.h"
#include "EntityIndexesEnum.h"

#include "EntityFactory.h"

namespace Entities
{
	const float PLAYER_JUMP_POWER = 5.0;

	EntityFactory::EntityFactory(b2World* world)
		:world_(world)
	{
	}

	b2Body* EntityFactory::createEntityBody(b2Vec2 position, b2BodyType bodyType, float width, float height)
	{
		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(position.x / Globals::PIXELS_PER_METER, position.y / Globals::PIXELS_PER_METER);
		b2Body* body = world_->CreateBody(&bodyDef);

		b2ChainShape chainShape;

		b2Vec2 vertices[8];
		vertices[7] = b2Vec2(-width / 2, -height / 2 + 0.01); // middle bottom left
		vertices[6] = b2Vec2(-width / 2, +height / 2 - 0.01); // middle top left
		vertices[5] = b2Vec2((-width / 2) + 0.03, +height / 2); // top left
		vertices[4] = b2Vec2(+ width / 2 - 0.03, +height / 2); // top right
		vertices[3] = b2Vec2(+ width / 2, +height / 2 - 0.01); // middle top right
		vertices[2] = b2Vec2(+ width / 2, -height / 2 + 0.01); // middle bottom right
		vertices[1] = b2Vec2(+ width / 2 - 0.03, -height / 2); // bottom right
		vertices[0] = b2Vec2((-width / 2) + 0.03, -height / 2); // bottom left
		chainShape.CreateLoop(vertices, 8);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &chainShape;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	Player* EntityFactory::createPlayer(b2Vec2 position, std::string modelName)
	{
		float playerWidth = Globals::DEFAULT_PLAYER_WIDTH / Globals::PIXELS_PER_METER,
			playerHeight = Globals::DEFAULT_PLAYER_HEIGHT / Globals::PIXELS_PER_METER;

		b2Body* body = Capsule::create(world_, position, playerWidth, playerHeight);

		body->GetFixtureList()->SetDensity(5.0);
		body->GetFixtureList()->SetFriction(0.3);

		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetUserData((void*)EntityIndexes::PlayerParts);
			fixture = fixture->GetNext();
		}

		//add foot sensor fixture
		float sensorDim = 0.1;
		b2Vec2 sensorCentre(0, -playerHeight / 2 - sensorDim / 2);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(sensorDim, sensorDim, sensorCentre, 0);

		b2FixtureDef SensorFixtureDef;
		SensorFixtureDef.shape = &polygonShape;
		SensorFixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&SensorFixtureDef);
		footSensorFixture->SetUserData((void*)EntityIndexes::FootSensor);

		GameEngine::RenderComponent rc("Models/Game/Player/Idle__001.png", b2Vec2(Globals::DEFAULT_PLAYER_WIDTH, Globals::DEFAULT_PLAYER_HEIGHT), body);
		GameEngine::AnimationComponent ac("Models/Game/Player", "Idle", 40, rc.getTextureName());
		Player* player = new Player(rc, ac, PLAYER_JUMP_POWER);
		return player;
	}

	Block* EntityFactory::createBlock(b2Vec2 position, std::string modelName)
	{
		float blockHeight = Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER,
			blockWidth = Globals::BLOCK_WIDTH / Globals::PIXELS_PER_METER;

		b2Body* body = createEntityBody(position, b2_staticBody, blockWidth, blockHeight);
		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != nullptr) {
			fixture->SetUserData((void*)EntityIndexes::Block);
			fixture = fixture->GetNext();
		}

		GameEngine::RenderComponent rc("Models/Game/Block/" + modelName + "__001.png", b2Vec2(Globals::BLOCK_WIDTH, Globals::BLOCK_HEIGHT), body);
		Block* block = new Block(rc);

		return block;
	}

	Tree* EntityFactory::createTree(b2Vec2 position, std::string modelName)
	{
		float treeHeight = Globals::TREE_HEIGHT,
			treeWidth = Globals::TREE_WIDTH;

		b2Body* body = createEntityBody(position, b2_staticBody, treeWidth, treeHeight);
		GameEngine::RenderComponent rc("Models/Game/Tree/" + modelName + "__001.png", b2Vec2(Globals::TREE_WIDTH, Globals::TREE_HEIGHT), body);
		Tree* tree = new Tree(rc);

		return tree;
	}

	EntityFactory::~EntityFactory()
	{
	}
}
