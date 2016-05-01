#include "Block.h"

namespace Entities
{
	Block::Block(b2Body* body, GameEngine::RenderComponent* rc)
		: GameEntity(body, rc)
	{
	}
}