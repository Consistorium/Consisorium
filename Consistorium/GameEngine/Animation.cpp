#include "Animation.h"

#include <filesystem/dirent.h>

namespace GameEngine {
	Animation::Animation(IAnimateable *animateable, std::string name, std::vector<std::string> frames)
		: animationName_(name),
		currentFrameIndex_(0),
		animateable_(animateable),
		frames_(frames),
		isLooping_(false)
	{
	}

	Animation::~Animation()
	{
	}

	int Animation::getCurrentFrameIndex()
	{
		return this->currentFrameIndex_;
	}

	void Animation::setCurrentFrameIndex(int val) 
	{
		if (val >= 0 && val < this->frames_.size())
		{
			this->currentFrameIndex_ = val;
		}
	}

	std::string Animation::getAnimationName()
	{
		return this->animationName_;
	}

	std::string Animation::getCurrentFrame()
	{
		return this->frames_[this->currentFrameIndex_];
	}

	int Animation::getNumberOfFrames()
	{
		return this->frames_.size();
	}

	void Animation::setIsLooping(bool isLooping)
	{
		this->isLooping_ = isLooping;
	}

	bool Animation::getIsLooping()
	{
		return this->isLooping_;
	}
}