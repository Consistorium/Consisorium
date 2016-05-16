#pragma once

#include <vector>
#include <Game\Entities\EntityTypes.h>
#include <Game\Entities\Player.h>

class GameState
{
	std::vector<b2Vec2> breakableIntervals_;
	int currentPlayerLevel_;
	Entities::Player *player_;
	GameState(Entities::Player *player);
	int playerKillRequirements_;
public:

	bool canBreakEntity(Entities::GameEntity *entity);

	void getEnemyKilledBonus();

	static GameState& get(Entities::Player *player)
	{
		static GameState INSTANCE(player);
		return INSTANCE;
	}
};

