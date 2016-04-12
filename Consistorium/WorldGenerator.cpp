#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(GameEngine::IGraphicsRenderer* renderer, b2World* world, std::vector<IWorldLayer*> layers)
	: renderer_(renderer),
	world_(world),
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
		layer->Generate(renderer_, world_, entities);
	}
}