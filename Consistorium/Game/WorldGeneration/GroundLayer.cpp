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

	int skipLength = 0; // used so specials places don't spawn inside each other
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
			std::shared_ptr<b2Vec2> center = place->getCenter();
			for (int k = 0; k < place->getElements().size(); k++)
			{
				int innerSize = place->getElements()[k].size();
				skipLength = std::max(skipLength, innerSize);
				for (int l = 0; l < innerSize; l++)
				{
					factory.createFromName(b2Vec2(i + (center->y + l)* Globals::BLOCK_WIDTH, max + (center->x - k) * Globals::BLOCK_WIDTH), place->getElements()[k][l]);
				}
			}
		}
	}
}