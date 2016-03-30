#include <Globals\Constants.h>

#include "EntityFactory.h"
#include "Player.h"

const float PLAYER_JUMP_POWER = 5.0;

EntityFactory::EntityFactory(b2World* world)
	:world_(world)
{
}

GameEntity* EntityFactory::createPlayer(b2Vec2 position, char* modelName)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world_->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	// Set the box density to be non-zero, so it will be dynamic.
	//density -> mass
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	//does not work if on stack
	//calls delete twice
	Player* player = new Player(
		body->GetPosition(), 
		modelName, 
		Globals::DEFAULT_PLAYER_WIDTH, 
		Globals::DEFAULT_PLAYER_HEIGHT, 
		PLAYER_JUMP_POWER);
	//add foot sensor fixture
	b2Vec2 footSensorCenter;
	footSensorCenter.x = position.x + player->getWidth() / 2;
	footSensorCenter.x = position.y + player->getHeight();
	
	polygonShape.SetAsBox(0.1, 0.1, b2Vec2(0, -2), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);


	player->setBody(body);
	player->setBodyDef(bodyDef);

	return player;
}

EntityFactory::~EntityFactory()
{
}