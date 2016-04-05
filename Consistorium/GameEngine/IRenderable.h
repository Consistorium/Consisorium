#pragma once

#include <string>
#include <Box2D\Box2D.h>
#include <SDL\SDL.h>

namespace GameEngine {
	class IRenderable
	{
	public:
		virtual ~IRenderable() { };

		virtual std::string* getTextureName() = 0;

		virtual b2Vec2 getScale(SDL_Rect textureSize) = 0;

		virtual b2Vec2 getSize() = 0;

		virtual b2Vec2 getPosition() = 0;
	};
}
