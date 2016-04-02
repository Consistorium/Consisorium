#include <Globals\Constants.h>

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
		bodyDef.position.Set(position.x, position.y);
		b2Body* body = world_->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(width / 2.0f, (height - width) / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	Player* EntityFactory::createPlayer(b2Vec2 position, char* modelName)
	{
		float playerWidth = Globals::DEFAULT_PLAYER_WIDTH / Globals::PIXELS_PER_METER,
			playerHeight = Globals::DEFAULT_PLAYER_HEIGHT / Globals::PIXELS_PER_METER;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.fixedRotation = true;
		b2Body* body = world_->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(playerWidth / 2.0f, (playerHeight - playerWidth) / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;

		body->CreateFixture(&fixtureDef);

		// Create the circles
		b2CircleShape circleShape;
		circleShape.m_radius = playerWidth / 2.0f;
		b2FixtureDef circleDef;
		circleDef.shape = &circleShape;
		circleDef.density = 5.0f;
		circleDef.friction = 0.3f;

		// Bottom circle
		circleShape.m_p.Set(0.0f, (-playerHeight + playerWidth) / 2.0f);
		body->CreateFixture(&fixtureDef);

		// Top Circle
		circleShape.m_p.Set(0.0f, (playerHeight - playerWidth) / 2.0f);
		body->CreateFixture(&circleDef);

		// Set the box density to be non-zero, so it will be dynamic.
		//density -> mass
		body->GetFixtureList()->SetDensity(5.0);
		body->GetFixtureList()->SetFriction(0.3);

		//add foot sensor fixture
		b2Vec2 footSensorCenter;
		footSensorCenter.x = position.x + playerWidth / 2;
		footSensorCenter.y = position.y + playerHeight / 2;

		//TODO:Create a circle body shape

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, -2), 0);

		b2FixtureDef SensorFixtureDef;
		SensorFixtureDef.shape = &polygonShape;
		SensorFixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&SensorFixtureDef);
		footSensorFixture->SetUserData((void*)3);

		GameEngine::RenderComponent rc("Models/Game/Player/Idle__001.png", b2Vec2(0.3, 0.3), b2Vec2(0, 0));
		GameEngine::AnimationComponent ac("Models/Game/Player", "Idle", 40, rc.getTextureName());
		Player* player = new Player(rc, ac, PLAYER_JUMP_POWER);
		player->setBody(body);
		return player;
	}

	GameEntity* EntityFactory::createBlock(b2Vec2 position, char* modelName)
	{
		float blockHeight = Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER,
			blockWidth = Globals::BLOCK_WIDTH / Globals::PIXELS_PER_METER;

		b2Body* body = createEntityBody(position, b2_staticBody, blockWidth, blockHeight);
		GameEngine::RenderComponent rc("Models/Game/Block/Normal__001.png", b2Vec2(1, 1), position);
		GameEntity* block = new Block(rc);
		block->setBody(body);
		return block;
	}

	EntityFactory::~EntityFactory()
	{
	}
}