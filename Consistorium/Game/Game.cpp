#include "Game.h"

#include <Game/Globals/Constants.h>
#include <KeyboardHandler.h>

#include "WorldGenerator.h"
#include "GroundLayer.h"
#include "UndergroundLayer.h"
#include "UI\InterfaceManager.h"
#include "Entities/EntityIndexesEnum.h"

using namespace Entities;

const b2Vec2 GRAVITY(0, -100);
const int CAMERA_SPEED = 50;

void moveCharacter(DynamicEntity* entity, int direction);
void jump(DynamicEntity* entity);
b2Vec2 getWorldCoordinates(SDL_Point clickPoint, DynamicEntity* player);

Game::Game(SDL_Window* window)
	: renderer_(window, Globals::PIXELS_PER_METER),
	Window(window),
	gravity_(GRAVITY),
	keyboardHandler_(new KeyboardHandler()),
	contactListener_(new JumpContactListener())
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
	EntityFactory entityFactory(world_, &renderer_, entities_);

	b2Vec2 playerPosition(1.0f, 4.0f);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");
	entities_.push_back(&player);
	SDL_Rect playerHealthPos;
	playerHealthPos.x = 500;
	playerHealthPos.y = 500;
	std::vector<Enemy*> enemies;

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
	world_->SetContactListener(contactListener_.get());

	SDL_Event e;
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
			case SDL_KEYUP:
				keyboardHandler_->handleKeyPress(e, e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMousePress(e, cameraPos, entityFactory);
				break;
			}
		}

		handleKeyPress(&player);

		world_->Step(timeStep_, velocityIterations_, positionIterations_);
		cameraPos.x = player.getPosition().x * Globals::PIXELS_PER_METER - Globals::SCREEN_WIDTH / 2;
		cameraPos.y = player.getPosition().y * Globals::PIXELS_PER_METER - Globals::SCREEN_HEIGHT / 2;
		renderer_.RenderAll(cameraPos);
		player.update();
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->iterateAI(player);
			enemies[i]->update();
		}

		interfaceManager.showHealth(playerHealthPos, "health", player.getHealth(), player.getHealth());

		if (timer.GetMilliseconds() > Globals::DAY_DURATION)
		{
			if (isDay)
			{
				isDay = false;
				renderer_.SetRenderColor(Globals::DAY_COLOR);
				for (size_t i = 0; i < enemies.size(); i++)
				{
					renderer_.RemoveRenderable(enemies[i]->getRenderableComponent());
					world_->DestroyBody(enemies[i]->getBody());
				}

				enemies.clear();
			}
			else
			{
				isDay = true;
				renderer_.SetRenderColor(Globals::NIGHT_COLOR);
				addEnemies(&entityFactory, &enemies);
			}

			timer.Reset();
		}
	
	}
}

void Game::handleKeyPress(DynamicEntity* player)
{
	if (keyboardHandler_->isPressed(SDLK_LEFT))
	{
		player->setXDirection(-1);
		player->move();
	}

	if (keyboardHandler_->isPressed(SDLK_RIGHT))
	{
		printf("GOING RIGHT \n");
		player->setXDirection(1);
		player->move();
	}

	if (keyboardHandler_->isPressed(SDLK_UP))
	{
		int contacts = contactListener_->getContactsCount();
		if (contactListener_->getContactsCount() >= 1 && jumpTimer_.GetMilliseconds() > 700)
		{
			printf("Jumping\n");
			player->jump(gravity_);
			jumpTimer_.Reset();
		}
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

void Game::handleMousePress(SDL_Event e, b2Vec2 camera, EntityFactory entityFactory)
{
	if (e.button.button == SDL_BUTTON_LEFT ||
		e.button.button == SDL_BUTTON_RIGHT)
	{
		SDL_Point clickPoint;
		SDL_GetMouseState(&clickPoint.x, &clickPoint.y);
		b2Vec2 worldCoords = getWorldCoordinates(clickPoint, camera);
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			b2Vec2 a(worldCoords.x * Globals::PIXELS_PER_METER, worldCoords.y * Globals::PIXELS_PER_METER);
			entityFactory.createBlock(a, "Grass");
			return;
		}
		for (size_t i = 0; i < entities_.size(); i++)
		{
			b2Vec2 entitySize = entities_[i]->getSize();
			entitySize.x /= Globals::PIXELS_PER_METER;\
			entitySize.y /= Globals::PIXELS_PER_METER;

			b2Vec2 entityCoords = entities_[i]->getPosition();
			if (clickedOnEntity(worldCoords, entityCoords, entitySize))
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (entities_[i]->getUserData() != (int)EntityIndexes::Player)
					{
						renderer_.RemoveRenderable(entities_[i]->getRenderableComponent());
						world_->DestroyBody(entities_[i]->getBody());
						entities_.erase(entities_.begin() + i);
						break;
					}
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

	//printf("Clicked at world: %f : %f\n", worldCoords.x, worldCoords.y);

	return worldCoords;
}

void Game::addEnemies(Entities::EntityFactory* factory, std::vector<Enemy*>* enemies) {
	for (size_t i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(x, 6.0f);
		Enemy* skeleton = factory->createSkeleton(skeletonPosition, "Idle");
		enemies->push_back(skeleton);
		entities_.push_back(skeleton);
		renderer_.AddRenderable(skeleton->getRenderableComponent());
	}

	for (size_t i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(-x, 6.0f);
		Enemy* skeleton = factory->createSkeleton(skeletonPosition, "Idle");
		enemies->push_back(skeleton);
		entities_.push_back(skeleton);
		renderer_.AddRenderable(skeleton->getRenderableComponent());
	}
}