#include "GroundLayer.h"


GroundLayer::GroundLayer()
{
}

GroundLayer::~GroundLayer()
{
}

b2Vec2 GroundLayer::GetLayerRange()
{
	return b2Vec2(0, 0);
}

void GroundLayer::Generate()
{
}