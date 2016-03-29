#pragma once

#include "IAnimateable.h"
#include "Animation.h"
#include "TextureManager.h"
#include <string>
#include <stack>
#include <vector>
#include <map>

namespace GameEngine {
	class AnimationManager
	{
	private:
		IAnimateable *animateable_;
		std::string defaultAnimation_;
		std::map<std::string, Animation*> entityAnimations_;
		std::stack<Animation*> animationStack_;
		float totalMillisecondsElapsed_;
		float animationTimer_;

		void loadEntityAnimations();
	public:
		AnimationManager(IAnimateable *animateable, std::string defaultAnimation);

		~AnimationManager();

		void setAnimation(std::string animationName, bool isLooping);

		void revertAnimation();

		void updateAnimation();
	};
}