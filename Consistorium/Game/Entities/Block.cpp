#include "Block.h"

namespace Entities
{
	std::string Block::getAnimationsFolder()
	{
		return "Models/Game/Block";
	}

	Block::Block(std::string defaultAnimation, float width, float height)
		:GameEntity(defaultAnimation, width, height)
	{
	}
}