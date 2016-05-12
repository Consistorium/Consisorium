#pragma once

#include <vector>
#include <map>
#include "Color.h"
#include "IGraphicsRenderer.h"
#include "TextureManager.h"
#include "BST.h"

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
		std::map<int, std::map<int, IRenderable*>> dynamicRenderables_;
		std::map<int, BinarySearchTree<float, IRenderable*>> staticRenderables_;
		WorldConstraints worldConstraints;
		int pixelsPerMeter_;
		Color renderColor_;
		std::vector<IRenderable*> ui_renderables;
		SDL_bool Renderer::shouldRender(b2Vec2& renderablePosition, b2Vec2& cameraPosition, int& width, int& height);
	public:
		Renderer(SDL_Window* window, int pixelsPerMeter);

		~Renderer();

		SDL_Renderer* getWindowRenderer() override;

		void AddRenderable(int zIndex, IRenderable *renderable) override;

		void RemoveRenderable(int zIndex, IRenderable *renderable) override;

		void RemoveRenderable(int zIndex, SDL_Point point) override;

		void RenderAll(b2Vec2 cameraPos) override;

		void SetRenderColor(Color color) override;

		void RenderUI(IRenderable *item);

		bool CompareZIndexes(IRenderable*, IRenderable*);
	};
}
