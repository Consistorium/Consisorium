#pragma once

#include <vector>
#include <GameEngine/IGraphicsRenderer.h>
#include "IWorldLayer.h"

class WorldGenerator
{
private:
	GameEngine::IGraphicsRenderer *renderer_;
	std::vector<IWorldLayer*> layers_;
	b2World *world_;
public:
	WorldGenerator(GameEngine::IGraphicsRenderer *renderer, b2World *world, std::vector<IWorldLayer*> layers);

	~WorldGenerator();

	void Build();
};

