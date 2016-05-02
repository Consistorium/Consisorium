#include "Player.h"

namespace Entities
{
	Player::Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac)
		: FluentEntity(body, rc, ac) // doesnt work with constants wtf
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