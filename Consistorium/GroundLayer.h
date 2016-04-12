#pragma once

#include "IWorldLayer.h"

class GroundLayer : public IWorldLayer
{
public:
	GroundLayer();

	~GroundLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world, std::vector<Entities::GameEntity*>* entities);
};

