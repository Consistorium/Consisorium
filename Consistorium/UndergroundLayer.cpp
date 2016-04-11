#include "UndergroundLayer.h"

#include "Game/Globals/Constants.h"
#include "Game/Entities/EntityFactory.h"

UndergroundLayer::UndergroundLayer()
{
}

UndergroundLayer::~UndergroundLayer()
{
}

b2Vec2 UndergroundLayer::GetLayerRange()
{
	return Globals::UNDERGROUND_LAYER_HEIGHT_RANGE;
}

void UndergroundLayer::Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world)
{
	Entities::EntityFactory factory(world);
	GameEngine::IRenderable *current;
	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (int j = GetLayerRange().x; j >= GetLayerRange().y; j -= Globals::BLOCK_WIDTH)
		{
			current = factory.createBlock(b2Vec2(i, j), "Ground")->getRenderableComponent();
			renderer->AddRenderable(current);
		}
	}
}