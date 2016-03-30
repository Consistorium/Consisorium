#include <Globals\Constants.h>

#include "Entities\GameEntity.h"
#include "Entities\EntityFactory.h"
#include "Game.h"

const b2Vec2 GRAVITY(0, -0.1);

void moveCharacter(GameEntity* entity, int direction);
void jump(GameEntity* entity);

Game::Game(SDL_Window* window)
	: renderer_(window),
	Window(window),
	gravity_(GRAVITY)
{	
}

Game::~Game()
{
}

void Game::Init()
{
	world_ = new b2World(gravity_);
	JumpContactListener listener;
	contactListener_ = &listener;

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world_->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 9.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	//The suggested iteration count for Box2D is 8 for velocity and 3 for position.
	timeStep_ = 1.0f / 60.0f;
	velocityIterations_ = 8;
	positionIterations_ = 3;
}

void Game::Run()
{
	Init();
	EntityFactory entityFactory(world_);
	b2Vec2 playerPosition(3, 4);
	GameEntity& player = *entityFactory.createPlayer(playerPosition, "Idle");

	//prevent jumping in mid air
	int playerFootContacts = 0;
	
	jumpTimer_.Reset();
	JumpContactListener listener;
	world_->SetContactListener(&listener);

	SDL_Event e;

	renderer_.AddRenderable(&player);

	int i = -1;
	while (true) {
		i++;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				//player.die();
				handleKeyPress(e, &player);
				break;
			default:
				break;
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);

		b2Vec2 position = player.getBody()->GetPosition();
		float32 angle = player.getBody()->GetAngle();

		renderer_.RenderAll();
	}
}

void Game::handleKeyPress(SDL_Event e, GameEntity* player) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		player->setXDirection(-1);
		moveCharacter(player, -1);
		break;
	case SDLK_RIGHT:
		player->setXDirection(1);
		moveCharacter(player, 1);
		break;
	case SDLK_UP:
		if (contactListener_->getContactsCount() >= 1 && jumpTimer_.GetMilliseconds() > 500)
		{
			std::cout << jumpTimer_.GetMilliseconds() << std::endl;
			jump(player);
			jumpTimer_.Reset();
		}

		break;
	}
}

void moveCharacter(GameEntity* entity, int direction)
{
	//std::cout << "speed: " << entity->getSpeed() << std::endl; this changes speed quite a bit
	entity->getBody()->ApplyLinearImpulse(b2Vec2(entity->getAccelerationImpulse(), 0), entity->getBody()->GetWorldCenter(), true);
}

void jump(GameEntity* entity)
{
	std::cout << GRAVITY.y << std::endl;
	float impulse = entity->getBody()->GetMass() * (-GRAVITY.y) * entity->getJumpPower();
	b2Vec2 force;
	force.x = 0;
	force.y = impulse;
	entity->getBody()->ApplyLinearImpulse(force, entity->getBody()->GetWorldCenter(), true);
}