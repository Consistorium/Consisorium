#include "Player.h"

namespace Entities
{
	Player::Player(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower)
		: DynamicEntity(rc, ac, jumpPower, PLAYER_MAX_SPEED)
	{
	}

	void Player::die()
	{
		//this->animationManager_.setAnimation("Run", false);
	}

	Player::~Player()
	{
	}
}