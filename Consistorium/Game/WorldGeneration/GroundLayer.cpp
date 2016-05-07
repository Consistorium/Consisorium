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

void GroundLayer::Generate(EntityManager& entityManager, SpecialPlacesManager& placesManager)
{
	Entities::EntityFactory factory(entityManager);
	GameEngine::IRenderable *current;
	auto min = std::min(GetLayerRange().x, GetLayerRange().y);
	auto max = std::max(GetLayerRange().x, GetLayerRange().y);

	int skipLength = 0; // Used so special places don't spawn inside each other.
	for (float i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (float j = min; j <= max; j += Globals::BLOCK_WIDTH)
		{
			factory.createBlock(b2Vec2(i, j), "Grass");
		}

		if (skipLength > 0)
		{
			skipLength--;
			continue;
		}

		std::shared_ptr<SpecialPlace> place = placesManager.getRandomPlace("Ground");

		if (rand() % *place->getFrequency() == 1)
		{
			placesManager.spawnPlace(b2Vec2(i, max), place, factory);
			skipLength = place->getWidth();
		}
		else if (skipLength == 0 && rand() % 5 == 1)
		{
			factory.createTree(b2Vec2(i, max), "Pine");
		}
	}
}