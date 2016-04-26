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
	Entities::EntityFactory factory(world, renderer, *entities);
	GameEngine::IRenderable *current;
	auto min = std::min(GetLayerRange().x, GetLayerRange().y);
	auto max = std::max(GetLayerRange().x, GetLayerRange().y);
	srand(time(nullptr));
	bool circle[5][5] =
	{
		{ false, true, true, true, false },
		{ true, true, true, true, true },
		{ true, true, true, true, true },
		{ false, true, true, true, false },
		{ false, false, true, false, false },
	};
	for (float i = -Globals::LAYER_WIDTH_IN_BLOCKS / 2; i < Globals::LAYER_WIDTH_IN_BLOCKS / 2; i += Globals::BLOCK_HEIGHT)
	{
		for (float j = min; j <= max; j += Globals::BLOCK_WIDTH)
		{
			factory.createBlock(b2Vec2(i, j), "Grass");
		}
		
		if ((rand() % 3 + 1) == 1)
		{
			Entities::Tree *tree = factory.createTree(b2Vec2(i, max + Globals::TREE_HEIGHT / 2 + Globals::BLOCK_HEIGHT / 2), "Pine");
			tree->getBody()->GetFixtureList()->SetSensor(true);
		}
		else if (rand() % 5 + 1 == 1)
		{
			b2Vec2 center(2 * Globals::BLOCK_WIDTH, 2 * Globals::BLOCK_WIDTH);
			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 5; l++)
				{
					if (circle[k][l])
					{
						factory.createBlock(b2Vec2(i - center.x + k * Globals::BLOCK_WIDTH, max - center.y + l *Globals::BLOCK_WIDTH), "Ground");
					}
				}
			}
		}
	}
}