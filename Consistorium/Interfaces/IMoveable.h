#pragma once

#include <iostream>

class IMoveable
{
private:
	float speed_;
public:
	IMoveable(float speed)
		: speed_(speed)
	{
	}

	virtual ~IMoveable()
	{ }

	virtual float getSpeed() { return this->speed_; }
	
	virtual void setSpeed(float value) { this->speed_ = value; }
};