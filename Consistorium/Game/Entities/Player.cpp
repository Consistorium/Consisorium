#include "Player.h"

namespace Entities
{
	Player::Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac, float jumpPower)
		: DynamicEntity(body, rc, ac, 0.2f, 10.0f) // doesnt work with constants wtf
	{
		setHealth(100);
	}

	void Player::dig()
	{
	}

	Player::~Player()
	{
	}
}