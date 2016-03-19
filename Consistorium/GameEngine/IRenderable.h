#pragma once

#include <SDL/SDL.h>
#include <memory>
#include "Vector2D.h"

namespace GameEngine {
	class IRenderable
	{
	public:
		virtual ~IRenderable() { };

		virtual char* getTextureName() = 0;

		virtual Vector2D getScreenPosition() = 0;
	};
}