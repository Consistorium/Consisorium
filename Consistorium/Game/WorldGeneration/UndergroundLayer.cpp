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

void UndergroundLayer::Generate(EntityManager& entityManager, SpecialPlacesManager& placesManager)
{
	Entities::EntityFactory factory(entityManager);
	GameEngine::IRenderable *current;
	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (int j = GetLayerRange().x; j >= GetLayerRange().y; j -= Globals::BLOCK_WIDTH)
		{
			factory.createBlock(b2Vec2(i, j), "Ground");
			/*Entities::Block* block = factory.createBlock(b2Vec2(i, j), "Ground");
			current = block->getRenderableComponent();
			entities->push_back(block);
			renderer->AddRenderable(current);*/
		}
	}
}