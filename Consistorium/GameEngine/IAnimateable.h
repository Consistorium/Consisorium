#pragma once

#include <string>

namespace GameEngine {
	class IAnimateable
	{
	public:
		virtual ~IAnimateable() { };

		virtual void setFrameTexture(std::string path) = 0;

		virtual std::string getAnimationsFolder() = 0;

		virtual double getAnimationSpeed() = 0;
	};
}