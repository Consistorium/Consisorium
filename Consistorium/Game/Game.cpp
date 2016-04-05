#include <Globals\Constants.h>
#include "Game.h"

using namespace Entities;

const b2Vec2 GRAVITY(0, -0.1);
const int CAMERA_SPEED = 20;

void moveCharacter(DynamicEntity* entity, int direction);
void jump(DynamicEntity* entity);

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
	groundBodyDef.position.Set(0.0f, 0);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	//The suggested iteration count for Box2D is 8 for velocity and 3 for position.
	timeStep_ = 1.0f / 60.0f;
	velocityIterations_ = 100;
	positionIterations_ = 50;
}

void Game::Run()
{
	Init();
	EntityFactory entityFactory(world_);
	b2Vec2 playerPosition(1, 4);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");
	
	b2Vec2 boxPosition;
	float boxHeight;

	float blockHeight = (Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER);

	/*b2Vec2 blockPosition;
	blockPosition.x = 0;
	blockPosition.y = 2 * blockHeight;
	GameEntity& block = *entityFactory.createBlock(blockPosition, "Normal");
	renderer_.AddRenderable(block.getRenderableComponent());*/

	for (size_t i = 1; i < 2; i++)
	{
		b2Vec2 blockPosition;
		blockPosition.x = i * (Globals::BLOCK_WIDTH) / Globals::PIXELS_PER_METER;
		blockPosition.y = blockHeight / 2;
		//blockPosition.x = i;
		//blockPosition.y = 1;
		GameEntity& block = *entityFactory.createBlock(blockPosition, "Normal");
		renderer_.AddRenderable(block.getRenderableComponent());
	}

	/*for (size_t i = 6; i < 11; i++)
	{
		b2Vec2 blockPosition;
		blockPosition.x = i * (Globals::BLOCK_WIDTH + 1) / Globals::PIXELS_PER_METER;
		blockPosition.y = blockHeight;
		GameEntity& block = *entityFactory.createBlock(blockPosition, "Normal");
		renderer_.AddRenderable(block.getRenderableComponent());
	}*/


	//prevent jumping in mid air
	int playerFootContacts = 0;
	
	jumpTimer_.Reset();
	JumpContactListener listener;
	world_->SetContactListener(&listener);

	SDL_Event e;

	renderer_.AddRenderable(player.getRenderableComponent());
	b2Vec2 cameraPos(0, 0);

	int i = -1;
	while (true) {
		i++;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				//player.die();
				handleKeyPress(e, cameraPos, &player);
				break;
			default:
				break;
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);
		renderer_.RenderAll(cameraPos);
		player.update();
	}
}

void Game::handleKeyPress(SDL_Event e, b2Vec2& cameraPos, DynamicEntity* player)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_w:
		cameraPos.y += CAMERA_SPEED;
		break;
	case SDLK_s:
		cameraPos.y -= CAMERA_SPEED;
		break;
	case SDLK_a:
		cameraPos.x += CAMERA_SPEED;
		break;
	case SDLK_d:
		cameraPos.x -= CAMERA_SPEED;
		break;
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

void moveCharacter(DynamicEntity* entity, int direction)
{
	float impulse = entity->getAccelerationImpulse();
	printf("float: %f \n", impulse);
	//printf("\nbefore: %f %f", entity->getBody()->GetPosition().x, entity->getBody()->GetPosition().y);
	entity->getBody()->ApplyLinearImpulse(b2Vec2(entity->getAccelerationImpulse(), 0), entity->getBody()->GetLocalCenter(), true);
	//printf("\nafter: %f %f\n", entity->getBody()->GetPosition().x, entity->getBody()->GetPosition().y);
}

void jump(DynamicEntity* entity)
{
	float impulse = entity->getBody()->GetMass() * (-GRAVITY.y) * entity->getJumpPower();
	b2Vec2 force(0, impulse);
	entity->getBody()->ApplyLinearImpulse(force, entity->getBody()->GetWorldCenter(), true);
}