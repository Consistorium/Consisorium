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

void UndergroundLayer::Generate(Entities::EntityFactory& factory, SpecialPlacesManager& placesManager)
{
	GameEngine::IRenderable *current;

	std::vector<std::vector<Entities::GameEntity*>> cache;
	for (int i = GetLayerRange().x; i >= GetLayerRange().y; i -= Globals::BLOCK_HEIGHT)
	{
		cache.push_back(std::vector<Entities::GameEntity*>());
		for (int j = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; j < Globals::LAYER_WIDTH_IN_BLOCKS / 2; j += Globals::BLOCK_WIDTH)
		{
			Entities::GameEntity* block = factory.createFromName(b2Vec2(j, i), "Ground");
			cache[cache.size() - 1].emplace_back(block);
		}
	}
	b2Vec2 worldCoords;
	for (int y = 0; y < cache.size(); y++)
	{
		for (int x = cache[y].size() - 1; x >= 0; x--)
		{
			std::shared_ptr<SpecialPlace> place = placesManager.getRandomPlace("Underground");

			if (rand() % *place->getFrequency() == 1)
			{
				if (cache[y][x] != nullptr) {
					worldCoords = cache[y][x]->getBody()->GetPosition();
					worldCoords.x *= Globals::PIXELS_PER_METER;
					worldCoords.y *= Globals::PIXELS_PER_METER;
					placesManager.spawnPlace(worldCoords, place, factory, cache, b2Vec2(x, y));
				}
			}
		}
	}
}