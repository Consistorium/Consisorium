#include "Renderer.h"
#include <iostream>
#include <algorithm>
#include "IRenderable.h"

namespace GameEngine
{
	Renderer::Renderer(SDL_Window* window, int pixelsPerMeter)
		: pixelsPerMeter_(pixelsPerMeter),
		windowRenderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
		textureManager_(windowRenderer_),
		window_(window),
		worldConstraints(SDL_GetWindowSurface(window)->w,
		SDL_GetWindowSurface(window)->h)
	{
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
		}
		else
		{
			this->dynamicRenderables_[zIndex][renderable->getId()] = renderable;
		}
	}

	void Renderer::RemoveRenderable(int zIndex, IRenderable *renderable)
	{
		if (!renderable->isStatic())
		{
			this->dynamicRenderables_[zIndex].erase(renderable->getId());
		}
		else
		{
			this->dynamicRenderables_[zIndex].erase(renderable->getId());
		}
	}

	void Renderer::RemoveRenderable(int zIndex, SDL_Point point)
	{
	}

	void Renderer::RenderAll(b2Vec2 cameraPos)
	{
		SDL_SetRenderDrawColor(windowRenderer_, renderColor_.r, renderColor_.g, renderColor_.b, renderColor_.a);

		SDL_RenderClear(this->windowRenderer_);
		SDL_Rect boundsRect;

		int screenWidth, screenHeight;
		SDL_GetWindowSize(window_, &screenWidth, &screenHeight);
		
		for (auto it = dynamicRenderables_.begin(); it != dynamicRenderables_.end(); ++it)
		{
			for (auto item : dynamicRenderables_[it->first])
			{
				if (item.second->alwaysRender())
				{
					RenderUI(item.second);
					continue;
				}

				b2Vec2 position = item.second->getPosition();
				if (shouldRender(position, cameraPos, screenWidth, screenHeight) == SDL_FALSE)
				{
					continue;
				}

				SDL_Texture *currentTexture = textureManager_.getTexture(*item.second->getTextureName());
				SDL_QueryTexture(currentTexture, nullptr, nullptr, &boundsRect.w, &boundsRect.h);
				b2Vec2 scale = item.second->getScale(boundsRect);
				SDL_RenderSetScale(this->windowRenderer_, item.second->getScale(boundsRect).x, item.second->getScale(boundsRect).y);
				boundsRect.x = (position.x * pixelsPerMeter_ - cameraPos.x - item.second->getSize().x / 2) / item.second->getScale(boundsRect).x;
				boundsRect.y = (screenHeight - position.y * pixelsPerMeter_ - item.second->getSize().y / 2 + cameraPos.y) / item.second->getScale(boundsRect).y;
				SDL_RendererFlip flip = ((item.second->getOrientation() == -1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
				SDL_RenderCopyEx(this->windowRenderer_, currentTexture, nullptr, &boundsRect, 0, nullptr, flip);
			}
		}
		

		SDL_RenderPresent(this->windowRenderer_);
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
		float renderAdvance = 1.5; // used for renderering a bigger are than the screen, so the player doesnt see the magic happen
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