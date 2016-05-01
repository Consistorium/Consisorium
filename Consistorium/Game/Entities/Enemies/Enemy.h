#pragma once

#include <vector>
#include <DynamicEntity.h>

namespace Entities
{
	class Enemy : public DynamicEntity
	{
	private:
		float scanRange_;
		float range_;
		float damage_;
		b2Timer attackTimer_;
		float haste_;
	public:
		Enemy(
			b2Body* body,
			GameEngine::RenderComponent* rc,
			GameEngine::AnimationComponent* ac,
			float jumpPower,
			float scanRange,
			float damage,
			float range,
			float haste);

		virtual void iterateAI(DynamicEntity& player);

		virtual int scan(DynamicEntity& player);

		virtual void tryAttack(DynamicEntity& player);
	};
}