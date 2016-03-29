#pragma once

#include <SDL/SDL.h>
#include <memory>
#include <string>
#include "Vector2D.h"

namespace GameEngine {
	class IRenderable
	{
	public:
		virtual ~IRenderable() { };

		virtual std::string getTextureName() = 0;

		virtual Vector2D getScreenPosition() = 0;

		virtual Vector2D getScale() = 0;
	};
}