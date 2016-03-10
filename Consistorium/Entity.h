#pragma once

class Entity
{
private:
	bool anchorState_;
public:
	Entity(bool anchorState);
	~Entity();

	virtual bool isAnchored();
	virtual void toggleAnchored();
};

