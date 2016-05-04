#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(EntityManager& entityManager, std::vector<IWorldLayer*> layers)
	: entityManager_(entityManager),
	layers_(layers)
{
}

WorldGenerator::~WorldGenerator()
{
}

void WorldGenerator::Build(std::vector<Entities::GameEntity*>* entities)
{
	for (IWorldLayer *layer : layers_)
	{
		layer->Generate(entityManager_, placesManager_);
	}
}