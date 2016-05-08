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

	std::vector<std::vector<Entities::GameEntity*>> cache;
	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		cache.push_back(std::vector<Entities::GameEntity*>());
		for (int j = GetLayerRange().x; j >= GetLayerRange().y; j -= Globals::BLOCK_WIDTH)
		{
			Entities::Block* block = factory.createBlock(b2Vec2(i, j), "Ground");
			cache[cache.size() - 1].emplace_back(block);
		}
	}

	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2, ii = 0; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; ii++, i += Globals::BLOCK_HEIGHT)
	{
		for (int j = GetLayerRange().x, jj = 0; j >= GetLayerRange().y; jj++, j -= Globals::BLOCK_WIDTH)
		{
			std::shared_ptr<SpecialPlace> place = placesManager.getRandomPlace("Underground");

			if (rand() % *place->getFrequency() == 1)
			{
				int x = (GetLayerRange().x - j) / Globals::BLOCK_WIDTH;
				int y = (i + Globals::LAYER_WIDTH_IN_BLOCKS / 2) / Globals::BLOCK_HEIGHT;
				placesManager.spawnPlace(b2Vec2(i, j), place, factory, cache, b2Vec2(x, y));
			}
		}
	}
}