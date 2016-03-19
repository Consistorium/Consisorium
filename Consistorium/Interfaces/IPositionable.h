#pragma once

#include <../GameEngine/Vector2D.h>

class IPositionable
{
private:
	GameEngine::Vector2D position_;
public:
	IPositionable(GameEngine::Vector2D position)
		: position_(position)
	{ }

	virtual ~IPositionable() { }

	virtual GameEngine::Vector2D getPosition() { return this->position_; }

	virtual void setPosition(GameEngine::Vector2D p) { this->position_.SetXY(p.X(), p.Y()); }
};