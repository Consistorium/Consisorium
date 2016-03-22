#pragma once

#include <SDL/SDL.h>
#include <memory>
#include <Box2D\Box2D.h>

namespace GameEngine {
	class IRenderable
	{
	public:
		virtual ~IRenderable() { };

		virtual char* getTextureName() = 0;

		virtual b2Vec2 getScreenPosition() = 0;
	};
}