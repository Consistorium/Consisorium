#pragma once

#include <vector>
#include <GameEngine\FluentEntity.h>

namespace Entities
{
	class Enemy : public FluentEntity
	{
	private:
		b2Timer attackTimer_;
	public:
		Enemy(
			b2Body* body,
			GameEngine::RenderComponent* rc,
			GameEngine::AnimationComponent* ac);

		virtual void iterateAI(FluentEntity& player);

		virtual int scan(FluentEntity& player);

		virtual void tryAttack(FluentEntity& player);
	};
}