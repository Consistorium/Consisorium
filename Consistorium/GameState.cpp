#include "GameState.h"

#include <Game\GameUtils.h>
#include <Game\Globals\Constants.h>

GameState::GameState(Entities::Player *player)
	: currentPlayerLevel_(0),
	playerKillRequirements_(0),
	player_(player)
{
	breakableIntervals_.push_back(Globals::AIR_LAYER_HEIGHT_RANGE);
	breakableIntervals_.push_back(Globals::GROUND_LAYER_HEIGHT_RANGE);
	breakableIntervals_.push_back(Globals::UNDERGROUND_LAYER_HEIGHT_RANGE);
}

bool GameState::canBreakEntity(Entities::GameEntity *entity)
{
	bool allowed = false;
	for (auto allowedInterval : breakableIntervals_)
	{
		auto y = entity->getPosition().y * Globals::PIXELS_PER_METER;
		if (GameUtils::isInInterval(y, allowedInterval))
		{
			allowed = true;
			break;
		}
	}

	return allowed;
}

void GameState::getEnemyKilledBonus()
{
	playerKillRequirements_++;
	if (playerKillRequirements_ < 2 && currentPlayerLevel_ != 3) {
		return;
	}

	playerKillRequirements_ = 0;

	currentPlayerLevel_++;
	if (currentPlayerLevel_ == 1) 
	{
		breakableIntervals_.push_back(Globals::RUIN_LAYER_HEIGHT_RANGE);
	}
	else if (currentPlayerLevel_ == 2)
	{
		breakableIntervals_.push_back(Globals::HELL_LAYER_HEIGHT_RANGE);
	}
	else if (currentPlayerLevel_ == 3)
	{
		breakableIntervals_.push_back(Globals::PURGATORY_LAYER_HEIGHT_RANGE);
	}
	else if (currentPlayerLevel_ >= 3 && GameUtils::isInInterval(player_->getPosition().y * Globals::PIXELS_PER_METER, Globals::PURGATORY_LAYER_HEIGHT_RANGE))
	{
		printf("You won the game gratz\n");
		player_->setHealth(0);
		return;
	}
}