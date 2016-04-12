#include "GroundLayer.h"

#include <algorithm>
#include <ctime>
#include <vector>

#include "Game/Globals/Constants.h"
#include "Game/Entities/EntityFactory.h"

GroundLayer::GroundLayer()
{
}

GroundLayer::~GroundLayer()
{
}

b2Vec2 GroundLayer::GetLayerRange()
{
	return Globals::GROUND_LAYER_HEIGHT_RANGE;
}

void GroundLayer::Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world, std::vector<Entities::GameEntity*>* entities)
{
	Entities::EntityFactory factory(world);
	GameEngine::IRenderable *current;
	auto min = std::min(GetLayerRange().x, GetLayerRange().y);
	auto max = std::max(GetLayerRange().x, GetLayerRange().y);
	srand(time(nullptr));
	for (float i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (float j = min; j <= max; j += Globals::BLOCK_WIDTH)
		{
			Entities::Block* block = factory.createBlock(b2Vec2(i, j), "Grass");
			current = block->getRenderableComponent();
			renderer->AddRenderable(current);
			entities->push_back(block);
		}
		
		if ((rand() % 3 + 1) == 1)
		{
			Entities::Tree *tree = factory.createTree(b2Vec2(i, max + Globals::TREE_HEIGHT / 2 + Globals::BLOCK_HEIGHT / 2), "Pine");
			tree->getBody()->GetFixtureList()->SetSensor(true);
			renderer->AddRenderable(tree->getRenderableComponent());
			entities->push_back(tree);
		}
	}
}
