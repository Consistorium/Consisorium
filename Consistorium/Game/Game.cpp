#include "Game.h"

#include <ctime>
#include <KeyboardHandler.h>
#include <Game/Globals/Constants.h>
#include <Game\BackgroundManager.h>
#include <Game\EventIds.h>
#include <Game\WorldGeneration\WorldGenerator.h>
#include <Game\WorldGeneration\GroundLayer.h>
#include <Game\WorldGeneration\UndergroundLayer.h>
#include <Game\WorldGeneration\RuinLayer.h>
#include <Game\UI\InterfaceManager.h>
#include <Game\Entities\EntityTypes.h>
#include <Game\WorldGeneration\SpecialPlacesManager.h>
#include <Game\Utils\SlotDescriptor.h>
#include <Game\Input\InputHandler.h>
#include <HellLayer.h>
#include <PurgatoryLayer.h>

using namespace Entities;

const b2Vec2 GRAVITY(0, -100);
const int CAMERA_SPEED = 50;

void moveCharacter(DynamicEntity* entity, int direction);

void jump(DynamicEntity* entity);

b2Vec2 getWorldCoordinates(SDL_Point clickPoint, DynamicEntity* player);

Game::Game(SDL_Window* window)
	: renderer_(window, Globals::PIXELS_PER_METER, b2Vec2(0, -Globals::TOTAL_LAYER_HEIGHT / 2), b2Vec2(Globals::LAYER_WIDTH_IN_BLOCKS / 1.8, Globals::TOTAL_LAYER_HEIGHT / 1.8)),
	Window(window),
	gravity_(GRAVITY),
	keyboardHandler_(new KeyboardHandler()),
	contactListener_(new PlayerContactListener(EventManager::get()))
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
	inventoryTimer_.Reset();
}

long stepSeconds = 0;

void Game::Run()
{
	Init();
	b2Vec2 cameraPos(0, 0);
	renderer_.RenderAll(cameraPos);
	EntityManager entityManager_(world_, &renderer_, entities_);
	std::vector<Enemy*> permantentlyLivingEnemies;
	EntityFactory entityFactory(entityManager_, permantentlyLivingEnemies);

	b2Vec2 playerPosition(1.0f, 4.0f);
	Player& player = *entityFactory.createPlayer(playerPosition, "Idle");
	interfaceManager_= new UI::InterfaceManager(&renderer_, window_, &player, EventManager::get());
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
	WorldGenerator worldGenerator(entityFactory, layers);
	worldGenerator.Build();
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

	EventManager::get().addWithParams(ON_REMOVE_ENTITY, [&](void*arg) {
		auto enemy = (Entities::Enemy*)(arg);
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemy->getId() == enemies[i]->getId())
			{
				enemies.erase(enemies.begin() + i);
			}
		}

		for (int i = 0; i < permantentlyLivingEnemies.size(); i++)
		{
			if (enemy->getId() == permantentlyLivingEnemies[i]->getId())
			{
				permantentlyLivingEnemies.erase(permantentlyLivingEnemies.begin() + i);
			}
		}

		return nullptr;
	});

	EventManager::get().add(ON_GET_HIT, [&]() {
		addEnemies(&entityFactory, &enemies);
	});

	BackgroundManager backgroundManager(&renderer_);
	Input::InputHandler inputHandler(keyboardHandler_.get(), interfaceManager_);
	float aiUpdateTimer = 0;
	while (player.getHealth() > 0) {
		stepSeconds = timer.GetMilliseconds();
		stepSeconds = stepSeconds > 1000 ? stepSeconds : 1000;
		float dt = timer.GetMilliseconds();
		timer.Reset();
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDLK_ESCAPE:
				player.setHealth(0);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboardHandler_->handleKeyPress(e, e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				inputHandler.handleMousePress(&player, &entityFactory, &entityManager_, e, cameraPos);
				break;
			}
		}

		inputHandler.handleKeyPress(&player, contactListener_.get(), gravity_, stepSeconds);
		world_->Step(timeStep_, velocityIterations_, positionIterations_);
		cameraPos.x = player.getPosition().x * Globals::PIXELS_PER_METER - Globals::SCREEN_WIDTH / 2;
		cameraPos.y = player.getPosition().y * Globals::PIXELS_PER_METER - Globals::SCREEN_HEIGHT / 2;
		player.update();
		renderer_.RenderAll(cameraPos);
		if (aiUpdateTimer > 0.3)
		{
			aiUpdateTimer = 0;
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (enemies[i] != nullptr)
				{
					enemies[i]->iterateAI(player, dt);
					enemies[i]->update();
				}
			}

			for (int i = 0; i < permantentlyLivingEnemies.size(); i++)
			{
				if (permantentlyLivingEnemies[i] != nullptr)
				{
					permantentlyLivingEnemies[i]->iterateAI(player, dt);
					permantentlyLivingEnemies[i]->update();
				}
			}
		}
		else 
		{
			aiUpdateTimer += dt;
		}

		backgroundManager.update(dt, player.getBody()->GetPosition());
	}
}

void Game::addEnemies(Entities::EntityFactory* factory, std::vector<Enemy*>* enemies) {
	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(x, 6.0f);
		Enemy* skeleton = factory->createEnemy(skeletonPosition, "Skeleton", "Idle");
		enemies->push_back(skeleton);
	}

	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 100 + 1;
		b2Vec2 skeletonPosition(-x, 6.0f);
		Enemy* skeleton = factory->createEnemy(skeletonPosition, "Skeleton", "Idle");
		enemies->push_back(skeleton);
	}
}