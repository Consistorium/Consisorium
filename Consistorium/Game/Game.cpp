#include <Globals\Constants.h>

#include "Entities\GameEntity.h"
#include "Game.h"
#include "Entities\EntityFactory.h"

void handleKeyPress(SDL_Event e, GameEntity* player);
void handleKeyRelease(SDL_Event e, GameEntity* player);
void moveCharacter(GameEntity* entity, int direction);
void jump(GameEntity* entity);

Game::Game(SDL_Window* window)
	:Window(window),
	renderer_(window),
	gravity_(0.0f, -10.0f)
{	
}

Game::~Game()
{
}

void Game::Init()
{
	world_ = new b2World(gravity_);

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
	b2Vec2 playerPosition;
	playerPosition.x = 3;
	playerPosition.y = 4;
	GameEntity& player = *entityFactory.createPlayer(playerPosition, "mainCharacter.png");

	SDL_Event e;

	renderer_.AddRenderable(&player);

	while (true) {
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				handleKeyPress(e, &player);
				break;
			case SDL_KEYUP:
				handleKeyPress(e, &player);
				break;
			default:
				break;
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);

		b2Vec2 position = player.getBody()->GetPosition();
		float32 angle = player.getBody()->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		renderer_.RenderAll();
	}
}

void handleKeyPress(SDL_Event e, GameEntity* player) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		player->setSpeed(-100);
		moveCharacter(player, -1);
		break;
	case SDLK_RIGHT:
		player->setSpeed(100);
		moveCharacter(player, 1);
		break;
	case SDLK_UP:
		jump(player);
		break;
	}
}

void handleKeyRelease(SDL_Event e, GameEntity* player)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
		player->setSpeed(0);
		break;
	}
}

void moveCharacter(GameEntity* entity, int direction)
{
	entity->getBody()->ApplyForceToCenter(b2Vec2(entity->getSpeed(), 0), true);
}

void jump(GameEntity* entity)
{
	float impulse = entity->getBody()->GetMass() * 5;
	entity->getBody()->ApplyLinearImpulse(b2Vec2(entity->getSpeed() / 2, impulse), entity->getBody()->GetWorldCenter(), true);
}