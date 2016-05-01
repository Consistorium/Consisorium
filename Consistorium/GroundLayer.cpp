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

	for (float i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (float j = min; j <= max; j += Globals::BLOCK_WIDTH)
		{
			factory.createBlock(b2Vec2(i, j), "Grass");
		}
		
		/*if ((rand() % 3 + 1) == 1)
		{
			Entities::Tree *tree = factory.createTree(b2Vec2(i, max + Globals::TREE_HEIGHT / 2 + Globals::BLOCK_HEIGHT / 2), "Pine");
			tree->getBody()->GetFixtureList()->SetSensor(true);
		}
		else */if (rand() % 5 + 1 == 1)
		{
			SpecialPlace *place = placesManager.getRandomPlace("Ground");
			std::unique_ptr<b2Vec2> center = place->getCenter();
			for (int k = 0; k < place->getElements().size(); k++)
			{
				for (int l = 0; l < place->getElements()[k].size(); l++)
				{
					factory.createFromName(b2Vec2(i - center->x - k * Globals::BLOCK_WIDTH, max + center->y + l * Globals::BLOCK_WIDTH), place->getElements()[k][l]);
				}
			}
		}
	}
}