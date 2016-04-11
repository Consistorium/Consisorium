#include "Player.h"

namespace Entities
{
	Player::Player(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower)
		: DynamicEntity(rc, ac, 0.2f, 10.0f) // doesnt work with constants wtf
	{
	}

	void Player::die()
	{
	}

	Player::~Player()
	{
	}
}