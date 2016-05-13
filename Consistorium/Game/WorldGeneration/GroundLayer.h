#pragma once

#include "IWorldLayer.h"

class GroundLayer : public IWorldLayer
{
public:
	GroundLayer();

	~GroundLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager) override;
};

