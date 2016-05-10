#pragma once

#include <Box2D\Common\b2Math.h>
#include <algorithm>

static class GameUtils
{
public:
	static bool isInInterval(float value, b2Vec2 interval);
};