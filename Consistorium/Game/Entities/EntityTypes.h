#pragma once

#include "UnCognizantEntityTypes.h"

class EntityTypes : public UnCognizantEntityTypes
{
public:
	enum
	{
		Player = UnCognizantEntityTypes::Last,
		Skeleton,
		DeathBoss
	};

	static bool isCognizant(int type)
	{
		return type >= UnCognizantEntityTypes::Last;
	};
};