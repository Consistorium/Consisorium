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
		}
	}
	int skipX = 0,
		skipY = 0;
	for (int i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (int j = GetLayerRange().x; j >= GetLayerRange().y; j -= Globals::BLOCK_WIDTH)
		{
			if (skipX > 0) 
			{ 
				skipX--; 
				continue;
			}
			std::shared_ptr<SpecialPlace> place = placesManager.getRandomPlace("Underground");

			auto center = place->getCenter();
			if (false)//rand() % *place->getFrequency() == 1)
			{
				placesManager.spawnPlace(b2Vec2(i, j), place, factory);
				skipX = place->getWidth() * 10;
				skipY = place->getHeight() * 10;
			}
		}
	}
}