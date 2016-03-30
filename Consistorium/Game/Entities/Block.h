#include "GameEntity.h"

namespace Entities
{
	class Block : public GameEntity
	{
	public:
		Block::Block(std::string defaultAnimation, float width, float height);
		std::string getAnimationsFolder() override;
	};
}