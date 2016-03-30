#pragma once

class IPositionable
{
private:
	b2Vec2 position_;
public:
	IPositionable(b2Vec2 position)
		: position_(position)
	{ }

	virtual ~IPositionable() { }

	virtual b2Vec2 getPosition() { return this->position_; }

	virtual void setPosition(b2Vec2 position) { this->position_.Set(position.x, position.y); }
};