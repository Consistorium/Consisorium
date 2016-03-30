#include "GameEntity.h"

namespace Entities
{
	class DynamicEntity : public GameEntity
	{
	protected:
		int xDirection_;
		float jumpPower_;
		float maxSpeed_;
	public:
		DynamicEntity(std::string modelName, float width, float height, float jumpPower, float maxSpeed);

		virtual float getJumpPower();

		virtual void setJumpPower(float power);

		virtual float getAccelerationImpulse();

		virtual void setXDirection(int direction);

		virtual ~DynamicEntity();
	};
}