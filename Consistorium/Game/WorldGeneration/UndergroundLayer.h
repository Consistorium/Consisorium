#pragma once

#include "IWorldLayer.h"

class UndergroundLayer : public IWorldLayer
{
public:
	UndergroundLayer();

	~UndergroundLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager) override;
};

