#pragma once

#include "GameEntity.h"

#include <RenderComponent.h>

namespace Entities
{
	class Tree : public GameEntity
	{
	public:
		Tree::Tree(GameEngine::RenderComponent rc);
	};
}