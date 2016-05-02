#pragma once

#include <GameEngine\DynamicEntity.h>

namespace Entities
{
	class FluentEntity : Entities::DynamicEntity
	{
		FluentEntity* withJumpPower(float value);

		FluentEntity* withScanRange(float value);

		FluentEntity* withDamage(float value);

		FluentEntity* withRange(float value);

		FluentEntity* withHaste(float value);

		FluentEntity* withMaxSpeed(float value);
	};
}