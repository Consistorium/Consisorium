#pragma once

#include "Game\WorldGeneration\IWorldLayer.h"

class HellLayer : public IWorldLayer
{
public:
	HellLayer();
	~HellLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(EntityManager& entityManager, SpecialPlacesManager& placesManager) override;
};

