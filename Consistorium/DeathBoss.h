#pragma once

#include <vector>
#include <GameEngine\FluentEntity.h>

namespace Entities
{
	class DeathBoss : public FluentEntity
	{
	private:
		b2Timer attackTimer_;
	public:
		DeathBoss(
			b2Body* body,
			GameEngine::RenderComponent* rc,
			GameEngine::AnimationComponent* ac);

		virtual void iterateAI(FluentEntity& player, float dt);

		virtual int scan(FluentEntity& player);

		bool locatedEnemy(b2Vec2 position, b2Vec2 enemyPosition, float range);

		virtual void tryAttack(FluentEntity& player);
	};
}