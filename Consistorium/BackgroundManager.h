#pragma once

#include <EventManager.h>
#include <IGraphicsRenderer.h>

class BackgroundManager
{
	const Color DAY_COLOR;
	const Color NIGHT_COLOR;
	const Color UNDERGROUND_COLOR;

	GameEngine::IGraphicsRenderer *renderer_;
	float timeElapsed_;
	bool isDay_;
public:
	BackgroundManager(GameEngine::IGraphicsRenderer *renderer);

	~BackgroundManager();

	void update(float dt, b2Vec2 playerPos);

	bool isDay();
};

