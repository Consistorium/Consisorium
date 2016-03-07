#pragma once

class IMoveable
{
private:
	float speed;
public:
	IMoveable(float speed)
		: speed(speed)
	{ }

	virtual ~IMoveable()
	{ }

	virtual float getSpeed() { return this->speed; }
	
	virtual void setSpeed(float value) { this->speed = value; }
};