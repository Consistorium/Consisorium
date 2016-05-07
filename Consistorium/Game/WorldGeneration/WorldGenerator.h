#pragma once

#include <vector>
#include <GameEngine/IGraphicsRenderer.h>
#include <GameEntity.h>
#include "IWorldLayer.h"
#include <Game\WorldGeneration\SpecialPlacesManager.h>

class WorldGenerator
{
private:
	std::vector<IWorldLayer*> layers_;
	EntityManager& entityManager_;
	SpecialPlacesManager placesManager_;
public:
	WorldGenerator(EntityManager& entityManager, std::vector<IWorldLayer*> layers);

	~WorldGenerator();

	void Build(std::map<int, Entities::GameEntity*>* entities);
};

