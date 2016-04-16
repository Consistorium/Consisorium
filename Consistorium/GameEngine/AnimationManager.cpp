#include "AnimationManager.h"

#include <filesystem\dirent.h>
#include "Utils.h"
#include <stdlib.h>
#include <vector>

namespace GameEngine {
	AnimationManager::AnimationManager(AnimationComponent animationComponent)
		: animationComponent_(animationComponent),
		totalMillisecondsElapsed_(0),
		animationTimer_(0)
	{
		loadEntityAnimations();
		setAnimation(animationComponent.getDefaultAnimation(), true);
	}


	AnimationManager::~AnimationManager()
	{
		// ??
	}

	void AnimationManager::loadEntityAnimations()
	{
		std::string folder = animationComponent_.getAnimationsFolder();

		std::map<std::string, std::vector<std::string>> animationMap;
		// read directory
		DIR *directory;
		struct dirent *dir;
		directory = opendir(folder.c_str());
		if (directory)
		{
			std::vector<std::string> result;

			while ((dir = readdir(directory)) != nullptr)
			{
				std::string s(dir->d_name);
				result.push_back(s);
			}

			closedir(directory);

			for (auto file : result)
			{
				auto fileParts = Utils::split(file, '_');
				auto fullName = animationComponent_.getAnimationsFolder() + '/' + file;
				animationMap[fileParts[0]].push_back(fullName);
			}


			for (auto pair : animationMap)
			{
				Animation *animation = new Animation(&animationComponent_, pair.first, pair.second);
				entityAnimations_[animation->getAnimationName()] = animation;
			}
		}
	}

	void AnimationManager::setAnimation(std::string animationName, bool isLooping)
	{
		if (entityAnimations_[animationName] == nullptr)
		{
			printf("Set Animation: No animation matches this name: %s\n.", animationName.c_str());
			return;
		}

		if (animationStack_.size() > 0)
		{
			if (animationStack_.top()->getAnimationName().compare(animationName) == 0)
			{
				return;
			}
		}

		entityAnimations_[animationName]->setIsLooping(isLooping);
		animationStack_.push(entityAnimations_[animationName]);
	}

	void AnimationManager::revertAnimation()
	{
		if (animationStack_.size() == 1)
		{
			return;
		}

		if (animationStack_.top()->getIsLooping() == false)
		{
			return;
		}

		animationStack_.top()->setCurrentFrameIndex(0);
		animationStack_.pop();
	}

	void AnimationManager::updateAnimation()
	{
		float deltaTime = SDL_GetTicks() - animationTimer_;

		if (animationStack_.top()->getNumberOfFrames() <= animationStack_.top()->getCurrentFrameIndex() + 1)
		{
			if (!animationStack_.top()->getIsLooping())
			{
				animationStack_.top()->setCurrentFrameIndex(0);
				animationStack_.pop();
			}

			animationStack_.top()->setCurrentFrameIndex(0);
			return;
		}

		totalMillisecondsElapsed_ += deltaTime;
		if (totalMillisecondsElapsed_ >= animationComponent_.getAnimationSpeed())
		{
			animationStack_.top()->setCurrentFrameIndex(animationStack_.top()->getCurrentFrameIndex() + 1);
			totalMillisecondsElapsed_ = 0;
		}

		animationComponent_.setFrameTexture(animationStack_.top()->getCurrentFrame());

		animationTimer_ = SDL_GetTicks();
	}
}