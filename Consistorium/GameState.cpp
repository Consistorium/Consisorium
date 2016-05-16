#include "GameState.h"

GameState::GameState(Entities::Player *player)
	: currentPlayerLevel_(0),
	playerKillRequirements_(0),
	player_(player)
{
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
		breakableBlocks_.push_back(EntityTypes::Ruin);
	}
	else if (currentPlayerLevel_ == 2)
	{
		breakableBlocks_.push_back(EntityTypes::Hell);
	}
	else if (currentPlayerLevel_ == 3)
	{
		breakableBlocks_.push_back(EntityTypes::PurgatoryBlock);
	}
	else if (currentPlayerLevel_ == 4)
	{
		printf("You won the game gratz\n");
	}
}

std::vector<int>* GameState::getPlayerBreakableBlocks()
{
	return &breakableBlocks_;
}