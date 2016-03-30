#include "Player.h"

namespace Entities
{
	Player::Player(std::string defaultAnimation, float width, float height, float jumpPower)
		: DynamicEntity(this->getAnimationsFolder() + "/" + defaultAnimation + "001.png", width, height, jumpPower, PLAYER_MAX_SPEED)
	{
	}

	std::string Player::getAnimationsFolder()
	{
		return "Models/Game/Player";
	}

	b2Vec2 Player::getScale()
	{
		b2Vec2 vec(0.2, 0.2);
		return vec;
	}


	void Player::die()
	{
		this->animationManager_.setAnimation("Run", false);
	}

	Player::~Player()
	{
	}
}