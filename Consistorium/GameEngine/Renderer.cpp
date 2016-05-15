#include "Renderer.h"
#include <iostream>
#include <algorithm>
#include "IRenderable.h"

namespace GameEngine
{
	Renderer::Renderer(SDL_Window* window, int pixelsPerMeter, b2Vec2 worldCenter, b2Vec2 halfDimensions)
		: pixelsPerMeter_(pixelsPerMeter),
		windowRenderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
		textureManager_(windowRenderer_),
		window_(window),
		staticRenderables_(XY(worldCenter.x, worldCenter.y), XY(halfDimensions.x * 1.5, halfDimensions.y)),
		worldConstraints(SDL_GetWindowSurface(window)->w,
		SDL_GetWindowSurface(window)->h)
	{
		SDL_GetWindowSize(window_, &screenWidth_, &screenHeight_);

		if (this->windowRenderer_ == NULL)
		{
			printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetRenderDrawColor(this->windowRenderer_, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(this->windowRenderer_);
		this->windowRenderer_ = NULL;
	}

	SDL_Renderer* Renderer::getWindowRenderer()
	{
		return this->windowRenderer_;
	}

	void Renderer::AddRenderable(int zIndex, IRenderable *renderable)
	{
		if(!renderable->isStatic())
		{
			this->dynamicRenderables_[zIndex][renderable->getId()] = renderable;
			return;
		}

		this->staticRenderables_.insert(renderable);
	}

	void Renderer::RemoveRenderable(int zIndex, IRenderable *renderable)
	{
		if (!renderable->isStatic())
		{
			this->dynamicRenderables_[zIndex].erase(renderable->getId());
			return;
		}
		
		staticRenderables_.remove(renderable);
	}

	void Renderer::RemoveRenderable(int zIndex, SDL_Point point)
	{
	}

	void Renderer::RenderAll(b2Vec2 cameraPos)
	{
		AABB cameraAABB(XY(cameraPos.x + screenWidth_ / 2, cameraPos.y + screenHeight_ / 2), XY(screenWidth_ / 2, screenHeight_ / 2));

		SDL_SetRenderDrawColor(windowRenderer_, renderColor_.r, renderColor_.g, renderColor_.b, renderColor_.a);
		SDL_RenderClear(this->windowRenderer_);

		std::vector<IRenderable*> result;
		staticRenderables_.queryRange(result, cameraAABB);
		for (auto item : result)
		{
			RenderItem(item, cameraPos);
		}

		for (auto zIndex : dynamicRenderables_)
		{
			for (auto entity : zIndex.second)
			{
				auto item = entity.second;
				RenderItem(item, cameraPos);
			}
		}
		

		SDL_RenderPresent(this->windowRenderer_);
	}

	void Renderer::RenderItem(IRenderable *item, b2Vec2 cameraPos)
	{
		SDL_Rect boundsRect;
		if (item->alwaysRender())
		{
			RenderUI(item);
			return;
		}

		b2Vec2 position = item->getPosition();
		if (shouldRender(position, cameraPos, screenWidth_, screenHeight_) == SDL_FALSE)
		{
			return;
		}

		SDL_Texture *currentTexture = textureManager_.getTexture(*item->getTextureName());
		SDL_QueryTexture(currentTexture, nullptr, nullptr, &boundsRect.w, &boundsRect.h);
		b2Vec2 scale = item->getScale(boundsRect);
		SDL_RenderSetScale(this->windowRenderer_, item->getScale(boundsRect).x, item->getScale(boundsRect).y);
		boundsRect.x = (position.x * pixelsPerMeter_ - cameraPos.x - item->getSize().x / 2) / item->getScale(boundsRect).x;
		boundsRect.y = (screenHeight_ - position.y * pixelsPerMeter_ - item->getSize().y / 2 + cameraPos.y) / item->getScale(boundsRect).y;
		SDL_RendererFlip flip = ((item->getOrientation() == -1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		SDL_RenderCopyEx(this->windowRenderer_, currentTexture, nullptr, &boundsRect, 0, nullptr, flip);
	}

	void Renderer::SetRenderColor(Color color)
	{
		renderColor_ = color;
	}

	SDL_bool Renderer::shouldRender(b2Vec2& renderablePosition, b2Vec2& cameraPosition, int& width, int& height)
	{
		SDL_Point point;
		point.x = renderablePosition.x * pixelsPerMeter_;
		point.y = renderablePosition.y * pixelsPerMeter_;
		SDL_Rect rect;
		float renderAdvance = 1.2; // used for renderering a bigger are than the screen, so the player doesnt see the magic happen
		rect.x = cameraPosition.x;
		rect.y = cameraPosition.y;
		
		rect.h = height * renderAdvance; // wtf why arent you working
		rect.w = width * renderAdvance;


		return SDL_PointInRect(&point, &rect);
	}

	void Renderer::RenderUI(IRenderable *item)
	{
		SDL_Rect boundsRect;

		int screenWidth, screenHeight;
		SDL_GetWindowSize(window_, &screenWidth, &screenHeight);
		SDL_Texture *currentTexture = textureManager_.getTexture(*item->getTextureName());
		SDL_QueryTexture(currentTexture, nullptr, nullptr, &boundsRect.w, &boundsRect.h);

		b2Vec2 scale = item->getScale(boundsRect);
		SDL_RenderSetScale(this->windowRenderer_, item->getScale(boundsRect).x, item->getScale(boundsRect).y);

		b2Vec2 position = item->getPosition();
		boundsRect.x = position.x / item->getScale(boundsRect).x;
		boundsRect.y = position.y / item->getScale(boundsRect).y;

		SDL_RenderCopy(this->windowRenderer_, currentTexture, nullptr, &boundsRect);
	}
}