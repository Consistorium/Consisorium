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

		virtual int getOrientation() = 0;

		virtual bool alwaysRender() = 0;

		virtual int getZIndex() = 0;

		virtual int getId() = 0;
	};
}
