#pragma once

#include <SDL/SDL.h>
#include <memory>
#include <string>
#include "Vector2D.h"
#include <Box2D\Box2D.h>

namespace GameEngine {
	class IRenderable
	{
	public:
		virtual ~IRenderable() { };

		virtual std::string getTextureName() = 0;

		virtual b2Vec2 getScale() = 0;

		virtual b2Vec2 getPosition() = 0;

		virtual float getWidth() = 0;

		virtual float getHeight() = 0;
	};
}