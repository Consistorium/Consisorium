#pragma once

#include <Box2D/Common/b2Math.h>
#include <IGraphicsRenderer.h>

class IWorldLayer
{
public:
	virtual ~IWorldLayer() { }
	
	virtual b2Vec2 GetLayerRange() = 0;

	virtual void Generate(GameEngine::IGraphicsRenderer *renderer, b2World *world) = 0;
};
