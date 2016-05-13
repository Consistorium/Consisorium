#pragma once

#include "Game\WorldGeneration\IWorldLayer.h"

class RuinLayer : public IWorldLayer
{
public:
	RuinLayer();
	~RuinLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(EntityManager& entityManager, SpecialPlacesManager& placesManager) override;
};

