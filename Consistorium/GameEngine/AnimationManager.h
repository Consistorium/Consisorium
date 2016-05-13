#pragma once

#include "AnimationComponent.h"
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
		AnimationComponent* animationComponent_;
		std::map<std::string, Animation*> entityAnimations_;
		std::stack<Animation*> animationStack_;
		float totalMillisecondsElapsed_;
		float animationTimer_;

		void loadEntityAnimations();
	public:
		AnimationManager(AnimationComponent* animationComponent_);

		~AnimationManager();

		void setAnimation(std::string animationName, bool isLooping);

		void revertAnimation();

		void revertAll();

		void updateAnimation();
	};
}