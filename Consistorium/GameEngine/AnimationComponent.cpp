#include "AnimationComponent.h"

namespace GameEngine {
	AnimationComponent::AnimationComponent(std::string folder, std::string defaultAnimation, double defaultSpeed, std::string *entityTexture)
		: entityTexture_(entityTexture),
		animationFolder_(folder),
		defaultAnimation_(defaultAnimation),
		animationSpeed_(defaultSpeed)
	{
	}


	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::setFrameTexture(std::string path)
	{
		*this->entityTexture_ = path;
	}

	std::string AnimationComponent::getDefaultAnimation()
	{
		return defaultAnimation_;
	}

	std::string AnimationComponent::getAnimationsFolder()
	{
		return this->animationFolder_;
	}

	double AnimationComponent::getAnimationSpeed()
	{
		return this->animationSpeed_;
	}
}