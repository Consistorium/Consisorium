#include "GameEntity.h"

#include <RenderComponent.h>

namespace Entities
{
	class Block : public GameEntity
	{
	public:
		Block::Block(GameEngine::RenderComponent rc);
	};
}