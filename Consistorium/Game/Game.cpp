#include <Game/Globals/Constants.h>
#include "Game.h"

#include "WorldGenerator.h"
#include "GroundLayer.h"
#include "UndergroundLayer.h"
#include "UI\InterfaceManager.h"

using namespace Entities;

const b2Vec2 GRAVITY(0, -100);
const int CAMERA_SPEED = 50;

void moveCharacter(DynamicEntity* entity, int direction);
void jump(DynamicEntity* entity);
b2Vec2 getWorldCoordinates(SDL_Point clickPoint, DynamicEntity* player);

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
	UI::InterfaceManager interfaceManager(windowSurface_);

	EntityFactory entityFactory(world_);
	b2Vec2 playerPosition(1.0f, 4.0f);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");
	entities_.push_back(&player);
	SDL_Rect playerHealthPos;
	playerHealthPos.x = 500;
	playerHealthPos.y = 500;

	b2Vec2 skeletonPosition(3.0f, 4.0f);
	Enemy& skeleton = *entityFactory.createSkeleton(skeletonPosition, "Idle");
	entities_.push_back(&skeleton);

	float blockHeight = (Globals::BLOCK_HEIGHT / Globals::PIXELS_PER_METER);
	
	std::vector<IWorldLayer*> layers;
	GroundLayer ground;
	layers.push_back(&ground);
	UndergroundLayer underground;
	layers.push_back(&underground);

	WorldGenerator worldGenerator(&renderer_, world_, layers);
	worldGenerator.Build(&entities_);

	//prevent jumping in mid air
	int playerFootContacts = 0;
	
	jumpTimer_.Reset();
	JumpContactListener listener;
	world_->SetContactListener(&listener);

	SDL_Event e;

	renderer_.AddRenderable(skeleton.getRenderableComponent());
	renderer_.AddRenderable(player.getRenderableComponent());
	b2Vec2 cameraPos(0, 0);

	b2Timer timer;
	bool isDay = true;
	renderer_.SetRenderColor(Globals::DAY_COLOR);
	while (true) {
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				// player.die();
				handleKeyPress(e, cameraPos, &player);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMousePress(e, cameraPos);
				break;
			default:
				break;
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);
		cameraPos.x = player.getPosition().x * Globals::PIXELS_PER_METER - Globals::SCREEN_WIDTH / 2;
		cameraPos.y = player.getPosition().y * Globals::PIXELS_PER_METER - Globals::SCREEN_HEIGHT / 2;
		renderer_.RenderAll(cameraPos);
		player.update();
		skeleton.iterateAI(player);
		skeleton.update();

		interfaceManager.showHealth(playerHealthPos, "health", player.getHealth(), player.getHealth());

		if (timer.GetMilliseconds() > Globals::DAY_DURATION)
		{
			if (isDay)
			{
				isDay = false;
				renderer_.SetRenderColor(Globals::DAY_COLOR);
			}
			else
			{
				isDay = true;
				renderer_.SetRenderColor(Globals::NIGHT_COLOR);
			}

			timer.Reset();
		}
	
	}
}

void Game::handleKeyPress(SDL_Event e, b2Vec2& cameraPos, DynamicEntity* player)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		player->setXDirection(-1);
		player->move();
		break;
	case SDLK_RIGHT:
		player->setXDirection(1);
		player->move();
		break;
	case SDLK_UP:
		int contacts = contactListener_->getContactsCount();
		if (contactListener_->getContactsCount() >= 1 && jumpTimer_.GetMilliseconds() > 1000)
		{
			player->jump(gravity_);
			jumpTimer_.Reset();
		}

		break;
	}
}

int clickedOnEntity(b2Vec2 clickPoint, b2Vec2 entityPosition, b2Vec2 entitySize)
{
	if ((clickPoint.x > entityPosition.x - entitySize.x / 2)
		&& (clickPoint.x < entityPosition.x + entitySize.x / 2))
	{
		if ((clickPoint.y < entityPosition.y + entitySize.y / 2)
			&& (clickPoint.y > entityPosition.y - entitySize.y / 2))
		{
			return 1;
		}
	}

	return 0;
}

void Game::handleMousePress(SDL_Event e, b2Vec2 camera)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point clickPoint;
		SDL_GetMouseState(&clickPoint.x, &clickPoint.y);
		b2Vec2 worldCoords = getWorldCoordinates(clickPoint, camera);

		for (size_t i = 0; i < entities_.size(); i++)
		{
			b2Vec2 entitySize = entities_[i]->getSize();
			entitySize.x /= Globals::PIXELS_PER_METER;
			entitySize.y /= Globals::PIXELS_PER_METER;

			b2Vec2 entityCoords = entities_[i]->getPosition();
			if (clickedOnEntity(worldCoords, entityCoords, entitySize))
			{
				if (entities_[i]->getUserData() == (int)EntityIndexes::Block)
				{
					renderer_.RemoveRenderable(entities_[i]->getRenderableComponent());
					world_->DestroyBody(entities_[i]->getBody());
					entities_.erase(entities_.begin() + i);
				}
			}
		}
	}
}

b2Vec2 Game::getWorldCoordinates(SDL_Point clickPoint, b2Vec2 camera)
{
	float clickHeight = Globals::SCREEN_HEIGHT - clickPoint.y;
	float renderingHeight = 4;
	b2Vec2 worldCoords;
	worldCoords.x = (camera.x + clickPoint.x) / Globals::PIXELS_PER_METER;
	worldCoords.y = (camera.y + clickHeight) / Globals::PIXELS_PER_METER - renderingHeight;

	printf("Clicked at world: %f : %f\n", worldCoords.x, worldCoords.y);

	return worldCoords;
}