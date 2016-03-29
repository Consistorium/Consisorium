#pragma once

#include <vector>
#include <string>
#include "IAnimateable.h"

namespace GameEngine {
	class Animation
	{
	private:
		IAnimateable *animateable_;
		int currentFrameIndex_;
		std::vector<std::string> frames_;
		std::string animationName_;
		bool isLooping_;
	public:
		Animation(IAnimateable *animateable, std::string name, std::vector<std::string> frames);

		~Animation();

		std::string getAnimationName();

		std::string getCurrentFrame();

		int getCurrentFrameIndex();

		void setCurrentFrameIndex(int val);

		int getNumberOfFrames();

		void setIsLooping(bool isLooping);

		bool getIsLooping();
	};
}