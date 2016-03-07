#pragma once

class IPositionable
{
private:
	float x, y;
public:
	IPositionable(float x, float y)
		: x(x), y(y)
	{ }

	virtual ~IPositionable() { }

	virtual float getX() { return this->x; }

	virtual void setX(float value) { this->x = value; }

	virtual float getY() { return this->y; }

	virtual void setY(float value) { this->y = value; }
};