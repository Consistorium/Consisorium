#include "GameState.h"

GameState::GameState(Entities::Player *player)
	: currentPlayerLevel_(0),
	player_(player)
{
}

void GameState::levelUpPlayer()
{
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
}

std::vector<int>* GameState::getPlayerBreakableBlocks()
{
	return &breakableBlocks_;
}


GameState::~GameState()
{
}
