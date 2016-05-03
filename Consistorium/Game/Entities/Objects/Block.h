#pragma once

#include "GameEntity.h"

#include <RenderComponent.h>

namespace Entities
{
	class Block : public GameEntity
	{
	public:
		Block::Block(b2Body* body, GameEngine::RenderComponent* rc);
	};
}