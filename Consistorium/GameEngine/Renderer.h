#pragma once

#include <vector>
#include <algorithm>
#include "IGraphicsRenderer.h"
#include "TextureManager.h"

namespace GameEngine
{
	class Renderer : public IGraphicsRenderer
	{
	private:
		SDL_Renderer *windowRenderer_;
		TextureManager textureManager_;
		std::vector<IRenderable*> renderables_;
	public:
		Renderer(SDL_Window* window);

		~Renderer();

		SDL_Renderer* getWindowRenderer() override;

		void AddRenderable(IRenderable *renderable) override;

		void RemoveRenderable(IRenderable *renderable) override;

		void RenderAll() override;
	};
}