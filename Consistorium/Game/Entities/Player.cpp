#include "Player.h"

namespace Entities
{
	Player::Player(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower)
		: DynamicEntity(rc, ac, 5.0f, 0.3f) // doesnt work with constants wtf
	{
	}

	void Player::die()
	{
	}

	Player::~Player()
	{
	}
}