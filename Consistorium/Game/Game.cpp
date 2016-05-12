#include "Game.h"

#include <Game/Globals/Constants.h>
#include <KeyboardHandler.h>

#include <Game\BackgroundManager.h>
#include <Game\EventIds.h>
#include "WorldGeneration\WorldGenerator.h"
#include "WorldGeneration\GroundLayer.h"
#include "WorldGeneration\UndergroundLayer.h"
#include <HellLayer.h>
#include <PurgatoryLayer.h>
#include "WorldGeneration\RuinLayer.h"
#include "UI\InterfaceManager.h"
#include "Entities/EntityTypes.h"
#include <Game\WorldGeneration\SpecialPlacesManager.h>
#include <ctime>

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
	srand(time(nullptr));
}

void Game::Run()
{
	Init();
	b2Vec2 cameraPos(0, 0);
	renderer_.RenderAll(cameraPos);

	EntityManager entityManager_(world_, &renderer_, entities_);
	EntityFactory entityFactory(entityManager_);
	b2Vec2 playerPosition(1.0f, 4.0f);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");
	interfaceManager_= new UI::InterfaceManager(&renderer_, window_, &player);
	interfaceManager_->showActionBar();
	entities_[player.getId()] = &player;
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
	RuinLayer ruins;
	layers.push_back(&ruins);
	HellLayer hell;
	layers.push_back(&hell);
	PurgatoryLayer purgatory;
	layers.push_back(&purgatory);
	WorldGenerator worldGenerator(entityManager_, layers);
	worldGenerator.Build(&entities_);
	//prevent jumping in mid air
	int playerFootContacts = 0;
	jumpTimer_.Reset();
	world_->SetContactListener(contactListener_.get());

	SDL_Event e;
	b2Timer timer;
	bool isDay = true;

	EventManager::get().add(ON_BECOME_DAY, [&]() {
		for (size_t i = 0; i < enemies.size(); i++)
		{
			renderer_.RemoveRenderable(enemies[i]->getZIndex(), enemies[i]->getRenderableComponent());
			world_->DestroyBody(enemies[i]->getBody());
		}
		enemies.clear();
	});

	EventManager::get().add(ON_BECOME_NIGHT, [&]() {
		addEnemies(&entityFactory, &enemies);
	});

	BackgroundManager backgroundManager(&renderer_);
	while (true) {
		float dt = timer.GetMilliseconds();
		timer.Reset();
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboardHandler_->handleKeyPress(e, e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMousePress(e, cameraPos, entityFactory, entityManager_, player);
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

		backgroundManager.update(dt, player.getBody()->GetPosition());
	}
}

void Game::handleKeyPress(DynamicEntity* player)
{
	if (keyboardHandler_->isPressed(SDLK_LEFT))
	{
		player->setXDirection(-1);
		player->move();
	}
	else if (keyboardHandler_->isPressed(SDLK_RIGHT))
	{
		player->setXDirection(1);
		player->move();
	}

	if (keyboardHandler_->isPressed(SDLK_UP))
	{
		int contacts = contactListener_->getContactsCount();
		if (contactListener_->getContactsCount() >= 1 && jumpTimer_.GetMilliseconds() > 700)
		{
			player->jump(gravity_);
			jumpTimer_.Reset();
		}
	}
}

void Game::handleMousePress(SDL_Event e, b2Vec2 camera, EntityFactory entityFactory, EntityManager& eManager, Player& player)
{
	SDL_Point clickPoint;
	SDL_GetMouseState(&clickPoint.x, &clickPoint.y);
	b2Vec2 worldCoords = eManager.getWorldCoordinates(clickPoint, camera);
	if (e.button.button == SDL_BUTTON_RIGHT)
	{
		entityFactory.createBlock(worldCoords, "Grass");
		return;
	}
	
	GameEntity* entity = eManager.getClickedEntity(worldCoords);
	
	if (entity != nullptr)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (entity->getUserData() != (int)EntityTypes::Player)
			{
				if (player.addToActionbar(entity))
				{
					interfaceManager_->updateAtionbar();
					world_->DestroyBody(entity->getBody());
				}
			}
		}
	}
}

void Game::addEnemies(Entities::EntityFactory* factory, std::vector<Enemy*>* enemies) {
	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(x, 6.0f);
		Enemy* skeleton = factory->createSkeleton(skeletonPosition, "Idle");
		enemies->push_back(skeleton);
	}

	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(-x, 6.0f);
		Enemy* skeleton = factory->createSkeleton(skeletonPosition, "Idle");
		enemies->push_back(skeleton);
	}
}