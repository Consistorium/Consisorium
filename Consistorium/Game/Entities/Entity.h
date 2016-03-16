#pragma once

class Entity
{
private:
	bool anchor_state_;
public:
	Entity(bool anchor_state);
	~Entity();

	bool isAnchored();
	bool toggleAnchored();
};

