#pragma once

#include "IWorldLayer.h"

class GroundLayer : public IWorldLayer
{
public:
	GroundLayer();

	~GroundLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(EntityManager& entityManager, SpecialPlacesManager& placesManager);
};

