#pragma once

#include "Player.h"
#include "../Interfaces/IMoveable.h"
#include "../Interfaces/IPositionable.h"
#include "../Interfaces/IVisible.h"
#include "Entity.h"

class Player : public Entity,
	public IMoveable,
	public IPositionable, public IVisible
{
public:
	Player(float beginX, float beginY, const char *modelName, bool anchorState);
	~Player();
};

