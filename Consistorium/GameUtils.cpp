#include "GameUtils.h"

bool GameUtils::isInInterval(float value, b2Vec2 interval)
{
	return (std::min(interval.x, interval.y) <= value) &&
		(std::max(interval.x, interval.y) >= value);
}