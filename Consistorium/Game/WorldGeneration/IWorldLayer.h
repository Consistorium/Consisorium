#pragma once

#include <Box2D/Common/b2Math.h>
#include <EntityManager.h>
#include <Game\WorldGeneration\SpecialPlacesManager.h>

class IWorldLayer
{
public:
	virtual ~IWorldLayer() { }
	
	virtual b2Vec2 GetLayerRange() = 0;

	virtual void Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager) = 0;
};
