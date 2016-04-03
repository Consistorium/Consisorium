#include "GameEntity.h"
#include <AnimationManager.h>

namespace Entities
{
	class DynamicEntity : public GameEntity
	{
	protected:
		int xDirection_;
		float jumpPower_;
		float maxSpeed_;
		GameEngine::AnimationComponent animationComponent_;
		GameEngine::AnimationManager animationManager_;
	public:
		DynamicEntity(GameEngine::RenderComponent& rc, GameEngine::AnimationComponent& ac, float jumpPower, float maxSpeed);

		virtual float getJumpPower();

		virtual void setJumpPower(float power);

		virtual float getAccelerationImpulse();

		virtual void update();

		virtual void setXDirection(int direction);

		GameEngine::IAnimateable* getAnimateableComponent();

		virtual ~DynamicEntity();
	};
}
