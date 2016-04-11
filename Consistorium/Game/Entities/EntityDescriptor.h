#pragma once

#include <string>
#include <Box2D\Box2D.h>

struct EntityDescriptor
{
	std::string animation;
	std::string modelName;
	std::string entityName;
	b2Vec2 position;
};