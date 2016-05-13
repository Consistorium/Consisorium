#pragma once

#include "GameEntity.h"

#include <RenderComponent.h>

namespace Entities
{
	class Bush : public GameEntity
	{
	public:
		Bush::Bush(b2Body* body, GameEngine::RenderComponent* rc);
	};
}