#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(Entities::EntityFactory& factory, std::vector<IWorldLayer*> layers)
	: factory_(factory),
	layers_(layers)
{
}

WorldGenerator::~WorldGenerator()
{
}

void WorldGenerator::Build()
{
	for (IWorldLayer *layer : layers_)
	{
		layer->Generate(factory_, placesManager_);
	}
}