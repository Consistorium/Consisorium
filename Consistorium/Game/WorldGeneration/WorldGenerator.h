#pragma once

#include <vector>
#include <GameEngine/IGraphicsRenderer.h>
#include <GameEntity.h>
#include <Game\Entities\Enemies\Enemy.h>
#include "IWorldLayer.h"
#include <Game\WorldGeneration\SpecialPlacesManager.h>

class WorldGenerator
{
private:
	std::vector<IWorldLayer*> layers_;
	Entities::EntityFactory& factory_;
	SpecialPlacesManager placesManager_;
public:
	WorldGenerator(Entities::EntityFactory& factory, std::vector<IWorldLayer*> layers);

	~WorldGenerator();

	void Build();
};

