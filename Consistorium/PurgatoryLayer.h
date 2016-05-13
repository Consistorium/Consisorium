#pragma once

#include "Game\WorldGeneration\IWorldLayer.h"

class PurgatoryLayer : public IWorldLayer
{
public:
	PurgatoryLayer();
	~PurgatoryLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager) override;
};

