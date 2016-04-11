#include "GroundLayer.h"

#include "Game/Globals/Constants.h"
#include "Game/Entities/EntityFactory.h"
#include <algorithm>

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

void GroundLayer::Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world)
{
	Entities::EntityFactory factory(world);
	Entities::Block *current;
	auto min = std::min(GetLayerRange().x, GetLayerRange().y);
	auto max = std::max(GetLayerRange().x, GetLayerRange().y);
	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS/2; i < Globals::LAYER_WIDTH_IN_BLOCKS/2; i += Globals::BLOCK_HEIGHT)
	{
		for (int j = min; j <= max; j += Globals::BLOCK_WIDTH)
		{
			current = factory.createBlock(b2Vec2(i, j), "Grass");
			renderer->AddRenderable(current->getRenderableComponent());
		}
	}
}