#pragma once

#include <vector>
#include <algorithm>

#include "IGraphicsRenderer.h"
#include "TextureManager.h"

namespace GameEngine
{
	struct WorldConstraints
	{
		WorldConstraints(float w, float h)
			: width(w),
			height(h)
		{
		}

		float width;
		float height;
	};

	class Renderer : public IGraphicsRenderer
	{
	private:
		SDL_Renderer *windowRenderer_;
		TextureManager textureManager_;
		SDL_Window *window_;
		std::vector<IRenderable*> renderables_;
		WorldConstraints worldConstraints;

		SDL_bool Renderer::shouldRender(b2Vec2& renderablePosition, b2Vec2& cameraPosition, int& width, int& height);
	public:
		Renderer(SDL_Window* window);

		~Renderer();

		SDL_Renderer* getWindowRenderer() override;

		void AddRenderable(IRenderable *renderable) override;

		void RemoveRenderable(IRenderable *renderable) override;

		void RemoveRenderable(SDL_Point point) override;

		void RenderAll(b2Vec2 cameraPos) override;
	};
}
