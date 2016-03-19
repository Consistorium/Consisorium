#pragma once

#include "IRenderable.h"

namespace GameEngine {
	class IGraphicsRenderer
	{
	public:
		virtual ~IGraphicsRenderer() { }

		virtual SDL_Renderer* getWindowRenderer() = 0;

		virtual void AddRenderable(IRenderable *renderable) = 0;

		virtual void RemoveRenderable(IRenderable *renderable) = 0;

		virtual void RenderAll() = 0;
	};
}