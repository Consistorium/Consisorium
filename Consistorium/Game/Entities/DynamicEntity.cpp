#include "DynamicEntity.h"

namespace Entities
{
	DynamicEntity::DynamicEntity(std::string modelName, float width, float height, float jumpPower, float maxSpeed)
		:GameEntity(modelName, width, height)
	{
		animationSpeed_ = 45;
		xDirection_ = 0;
		maxSpeed_ = maxSpeed;
		jumpPower_ = jumpPower;
	}

	DynamicEntity::~DynamicEntity()
	{
	}


	void DynamicEntity::setXDirection(int direction)
	{
		xDirection_ = direction;
	}

	void DynamicEntity::setJumpPower(float power)
	{
		jumpPower_ = power;
	}

	float DynamicEntity::getJumpPower()
	{
		return jumpPower_;
	}

	float DynamicEntity::getAccelerationImpulse()
	{
		float xVelocity = body_->GetLinearVelocity().x;

		return (maxSpeed_ - (xVelocity * xDirection_)) * xDirection_;
	}
}