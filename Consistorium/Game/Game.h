#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <SDL/SDL.h>
#include <Box2D\Box2D.h>
#include <UI\Window.h>
#include <Renderer.h>
#include <AnimationManager.h>
#include <KeyboardHandler.h>
#include <EntityManager.h>

#include "Game.h"
#include "Entities\EntityFactory.h"
#include "Utils\JumpContactListener.h"
#include "UI\InterfaceManager.h"

class Game : public GameEngine::Window
{
private:
	GameEngine::Renderer renderer_;
	void Init();
	b2World* world_;
	float32 timeStep_;
	int32 velocityIterations_;
	int32 positionIterations_;
	b2Vec2 gravity_;
	b2Timer jumpTimer_,
		inventoryTimer_;
	std::unique_ptr<JumpContactListener> contactListener_;
	std::map<int, Entities::GameEntity*> entities_;
	std::unique_ptr<KeyboardHandler> keyboardHandler_;
	UI::InterfaceManager* interfaceManager_;
public:
	Game(SDL_Window* window);

	~Game();

	void handleKeyPress(Entities::DynamicEntity* player);

	void handleMousePress(SDL_Event e, b2Vec2 camera, Entities::EntityFactory entityFactory, EntityManager& eManager, Entities::Player& player);

	void addEnemies(Entities::EntityFactory* factory, std::vector<Entities::Enemy*>* enemies);

	void Run();
};
