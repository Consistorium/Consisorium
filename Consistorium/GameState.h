#pragma once

#include <vector>
#include <Game\Entities\EntityTypes.h>
#include <Game\Entities\Player.h>

class GameState
{
	std::vector<int> breakableBlocks_;
	int currentPlayerLevel_;
	Entities::Player *player_;
	GameState(Entities::Player *player);
	int playerKillRequirements_;
public:

	void getEnemyKilledBonus();

	std::vector<int>* getPlayerBreakableBlocks();

	static GameState& get(Entities::Player *player)
	{
		static GameState INSTANCE(player);
		return INSTANCE;
	}
};

