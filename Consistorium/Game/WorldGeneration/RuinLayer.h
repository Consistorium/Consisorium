#pragma once

#include "IWorldLayer.h"

class RuinLayer : public IWorldLayer
{
public:
	RuinLayer();
	~RuinLayer();

	b2Vec2 GetLayerRange() override;

	void Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager) override;
};

