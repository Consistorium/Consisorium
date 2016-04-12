#pragma once

#include "IWorldLayer.h"
#include <vector>

class UndergroundLayer : public IWorldLayer
{
public:
	UndergroundLayer();

	~UndergroundLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world, std::vector<Entities::GameEntity*>* entities) override;
};

