#include "Enemy.h"

#include <Game\Globals\Constants.h>
#include "../EntityIndexesEnum.h"

namespace Entities
{
	Enemy::Enemy(
		GameEngine::RenderComponent& rc,
		GameEngine::AnimationComponent& ac,
		float jumpPower,
		float scanRange,
		float damage,
		float range,
		float haste)
		:DynamicEntity(rc, ac, jumpPower, 8.0f),
		scanRange_(scanRange),
		damage_(damage),
		range_(range),
		haste_(haste)
	{
		attackTimer_.Reset();
	}

	void Enemy::iterateAI(DynamicEntity& player)
	{
		setXDirection(scan(player));
		if (xDirection_ != 0)
		{
			animationManager_.setAnimation("Walk", true);
			move();
		}
		else
		{
			animationManager_.revertAnimation();
		}

		tryAttack(player);
	}

	int locatedEnemy(b2Vec2 position, b2Vec2 enemyPosition, float range)
	{
		return abs(position.x - enemyPosition.x) < range;
	}

	int  Enemy::scan(DynamicEntity& player)
	{
		if (locatedEnemy(getPosition(), player.getPosition(), scanRange_) &&
			(int)player.getUserData() == (int)EntityIndexes::Player)
		{
			float delta = ceil((getSize().x / 2 + player.getSize().x / 2) / Globals::PIXELS_PER_METER);
			if (getPosition().x - player.getPosition().x > delta)
			{
				return -1;
			}
			else if (player.getPosition().x - getPosition().x > delta)
			{
				return 1;
			}
		}

		return 0;
	}

	void Enemy::tryAttack(DynamicEntity& player)
	{
		float deltaX = ceil(getPosition().x - player.getPosition().x),
			deltaY = ceil(getPosition().y - player.getPosition().y);
		if (deltaX < range_ || deltaY < range_)
		{
			if (attackTimer_.GetMilliseconds()  > 1000 / haste_ )
			{
				animationManager_.setAnimation("Attack", false);
				attackTimer_.Reset();
				player.setHealth(player.getHealth() - damage_);
			}
		}
	}
}