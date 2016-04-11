#include <Game/Globals/Constants.h>
#include "Game.h"

#include "WorldGenerator.h"
#include "GroundLayer.h"
#include "UndergroundLayer.h"

using namespace Entities;

const b2Vec2 GRAVITY(0, -100);
const int CAMERA_SPEED = 50;

void moveCharacter(DynamicEntity* entity, int direction);
void jump(DynamicEntity* entity);

Game::Game(SDL_Window* window)
	: renderer_(window, Globals::PIXELS_PER_METER),
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
	velocityIterations_ = 8;
	positionIterations_ = 3;
}

void Game::Run()
{
	Init();
	EntityFactory entityFactory(world_);
	b2Vec2 playerPosition(1.0f, 4.0f);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");

	b2Vec2 skeletonPosition(3.0f, 4.0f);
	Skeleton& skeleton = *entityFactory.createSkeleton(skeletonPosition, "Idle");

	float blockHeight = (Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER);
	
	std::vector<IWorldLayer*> layers;
	GroundLayer ground;
	layers.push_back(&ground);
	UndergroundLayer underground;
	layers.push_back(&underground);

	WorldGenerator worldGenerator(&renderer_, world_, layers);
	worldGenerator.Build();

	//prevent jumping in mid air
	int playerFootContacts = 0;
	
	jumpTimer_.Reset();
	JumpContactListener listener;
	world_->SetContactListener(&listener);

	SDL_Event e;

	renderer_.AddRenderable(skeleton.getRenderableComponent());
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
				// player.die();
				handleKeyPress(e, cameraPos, &player);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMousePress(e);
				break;
			default:
				break;
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);
		cameraPos.x = -(player.getBody()->GetPosition().x * Globals::PIXELS_PER_METER - Globals::SCREEN_WIDTH / 2);
		cameraPos.y = player.getBody()->GetPosition().y * Globals::PIXELS_PER_METER - Globals::SCREEN_HEIGHT / 2;
		renderer_.RenderAll(cameraPos);
		player.update();
		skeleton.update();
	}
}

void Game::handleKeyPress(SDL_Event e, b2Vec2& cameraPos, DynamicEntity* player)
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
		int contacts = contactListener_->getContactsCount();
		if (contactListener_->getContactsCount() >= 1 && jumpTimer_.GetMilliseconds() > 1000)
		{
			jump(player);
			jumpTimer_.Reset();
		}

		break;
	}
}

void Game::handleMousePress(SDL_Event e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point clickPoint;
		SDL_GetGlobalMouseState(&clickPoint.x, &clickPoint.y);
		printf("%d %d\n", clickPoint.x, clickPoint.y);
	}
}

void moveCharacter(DynamicEntity* entity, int direction)
{
	float impulse = entity->getAccelerationImpulse();
	b2Vec2 force(impulse, 0);
	entity->getBody()->ApplyLinearImpulse(force, entity->getBody()->GetWorldCenter(), true);
}

void jump(DynamicEntity* entity)
{
	float impulse = entity->getBody()->GetMass() * (-GRAVITY.y) * entity->getJumpPower();
	b2Vec2 force(0, impulse);
	entity->getBody()->ApplyLinearImpulse(force, entity->getBody()->GetWorldCenter(), true);
}