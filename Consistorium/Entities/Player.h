#pragma once

#include "Player.h"
#include "../Interfaces/IMoveable.h"
#include "../Interfaces/IPositionable.h"
#include "../Interfaces/IVisible.h"

class Player : public IMoveable, public IPositionable, public IVisible
{
private:
	const float PLAYER_SPEED = 50;
public:
	Player(float beginX, float beginY, const char* modelName);
	~Player();
};

