#pragma once

#include <Box2D/Common/b2Math.h>

class IWorldLayer
{
public:
	virtual ~IWorldLayer() {}
	
	virtual b2Vec2 GetLayerRange() = 0;

	virtual void Generate() = 0;
};
