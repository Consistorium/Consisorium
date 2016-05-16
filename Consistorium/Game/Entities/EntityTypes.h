#pragma once

#include "UnCognizantEntityTypes.h"

class EntityTypes : public UnCognizantEntityTypes
{
public:
	enum
	{
		Player = UnCognizantEntityTypes::Last,
		Skeleton,
		DeathBoss,
		DarkSaber
	};

	static bool isCognizant(int type)
	{
		return type >= UnCognizantEntityTypes::Last;
	};
};