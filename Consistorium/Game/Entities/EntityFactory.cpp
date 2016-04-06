#include <vector>
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
		boxShape.SetAsBox(playerWidth / 2.0f, playerHeight / 2.0f);
		//boxShape.SetAsBox(playerWidth / 2.0f, (playerHeight - playerWidth) / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;

		body->CreateFixture(&fixtureDef);

		float halfHeight = (playerHeight - playerWidth) / 2;
		const int DIVISIONS = 8;
		const float RADIUS = playerWidth / 2;

		b2Vec2 vertices[DIVISIONS];
		b2PolygonShape circleShape;

		//BOTTOM CIRCLE
		for (int div = 1; div <= DIVISIONS; div++)
		{
			float32 angle = M_PI + (M_PI / div);
			float32 xPos, yPos;

			xPos = RADIUS * cosf(angle);
			yPos = -halfHeight + RADIUS * sinf(angle);
			vertices[div - 1] = b2Vec2(xPos, yPos);
		}

		circleShape.Set(vertices, DIVISIONS);
		b2FixtureDef circleDef;
		circleDef.shape = &circleShape;
		body->CreateFixture(&circleDef);

		//TOP CIRCLE
		for (int div = 1; div <= DIVISIONS; div++)
		{
			float32 angle = M_PI / div;
			float32 xPos, yPos;

			xPos = RADIUS * cosf(angle);
			yPos = -halfHeight + RADIUS * sinf(angle);
			vertices[div - 1] = b2Vec2(xPos, yPos);
		}

		circleShape.Set(vertices, DIVISIONS);
		circleDef.shape = &circleShape;
		body->CreateFixture(&circleDef);

		body->GetFixtureList()->SetDensity(5.0);
		body->GetFixtureList()->SetFriction(0.3);

		//add foot sensor fixture
		b2Vec2 footSensorCenter;
		footSensorCenter.x = position.x + playerWidth / 2;
		footSensorCenter.y = position.y - playerHeight / 2;

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, -2), 0);

		b2FixtureDef SensorFixtureDef;
		SensorFixtureDef.shape = &polygonShape;
		SensorFixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&SensorFixtureDef);
		footSensorFixture->SetUserData((void*)3);

		GameEngine::RenderComponent rc("Models/Game/Player/Idle__001.png", b2Vec2(1, 1), b2Vec2(Globals::DEFAULT_PLAYER_WIDTH, Globals::DEFAULT_PLAYER_HEIGHT), body);
		GameEngine::AnimationComponent ac("Models/Game/Player", "Idle", 40, rc.getTextureName());
		Player* player = new Player(rc, ac, PLAYER_JUMP_POWER);
		return player;
	}

	GameEntity* EntityFactory::createBlock(b2Vec2 position, char* modelName)
	{
		float blockHeight = Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER,
			blockWidth = Globals::BLOCK_WIDTH / Globals::PIXELS_PER_METER;

		b2Body* body = createEntityBody(position, b2_staticBody, blockWidth, blockHeight);
		GameEngine::RenderComponent rc("Models/Game/Block/Normal__001.png", b2Vec2(1, 1), b2Vec2(Globals::BLOCK_WIDTH, Globals::BLOCK_HEIGHT), body);
		GameEntity* block = new Block(rc);
		return block;
	}

	EntityFactory::~EntityFactory()
	{
	}
}