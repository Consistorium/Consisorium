#pragma once

#include "IAnimateable.h"

namespace GameEngine {
	class AnimationComponent : public IAnimateable
	{
	private:
		std::string animationFolder_;
		std::string defaultAnimation_;
		double animationSpeed_;
		std::string *entityTexture_;
	public:
		AnimationComponent(std::string folder, std::string defaultAnimation, double defaultSpeed, std::string *entityTexture);

		~AnimationComponent();

		void setFrameTexture(std::string path) override;

		std::string getAnimationsFolder() override;

		std::string getDefaultAnimation();

		double getAnimationSpeed() override;
	};
}