#pragma once

#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include <UI/Window.h>
#include <../GameEngine/Renderer.h>
#include <../GameEngine/AnimationManager.h>
#include <Box2D\Box2D.h>
#include <SDL/SDL.h>
#include <Renderer.h>
#include <UI/Window.h>

#include "Game.h"
#include "Entities\EntityFactory.h"
#include "Utils\JumpContactListener.h"

class Game : public Window
{
private:
	GameEngine::Renderer renderer_;
	void Init();
	b2World* world_;
	float32 timeStep_;
	int32 velocityIterations_;
	int32 positionIterations_;
	b2Vec2 gravity_;
	b2Timer jumpTimer_;
	JumpContactListener* contactListener_;
	std::vector<Entities::GameEntity*> entities_;
public:
	Game(SDL_Window* window);

	~Game();

	void handleKeyPress(SDL_Event e, b2Vec2& cameraPos, Entities::DynamicEntity* player);

	void handleMousePress(SDL_Event e, b2Vec2 camera);

	b2Vec2 getWorldCoordinates(SDL_Point clickPoint, b2Vec2 camera);

	void Run();
};