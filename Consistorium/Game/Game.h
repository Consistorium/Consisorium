#pragma once

#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL/SDL.h>
#include <Renderer.h>
#include <UI/Window.h>

#include "Game.h"
#include "Entities/Player.h"

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks);
void moveCharacter(Player* player, float deltaTicks, int direction);

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
public:
	Game(SDL_Window* window);

	~Game();

	void Run();
};