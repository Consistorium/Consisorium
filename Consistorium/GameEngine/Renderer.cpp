#include "Renderer.h"
#include <iostream>
#include "IRenderable.h"
#include "EngineConstants.h"

namespace GameEngine 
{
	Renderer::Renderer(SDL_Window* window)
		: windowRenderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
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

	void Renderer::AddRenderable(IRenderable *renderable)
	{
		this->renderables_.push_back(renderable);
	}

	void Renderer::RemoveRenderable(IRenderable *renderable)
	{
		this->renderables_.erase(
			std::remove(
				this->renderables_.begin(),
				this->renderables_.end(),
				renderable),
			this->renderables_.end());
	}

	void Renderer::RenderAll(b2Vec2 cameraPos)
	{
		SDL_RenderClear(this->windowRenderer_);
		SDL_Rect boundsRect;

		SDL_SetRenderDrawColor(windowRenderer_, 52, 152, 219, 255);
		SDL_Rect rectangle;

		int screenWidth, screenHeight;
		SDL_GetWindowSize(window_, &screenWidth, &screenHeight);

		rectangle.x = 0;
		rectangle.y = 0;
		rectangle.w = screenWidth;
		rectangle.h = screenHeight;

		SDL_RenderFillRect(windowRenderer_, &rectangle);

		for (IRenderable *item : this->renderables_)
		{
			b2Vec2 position = item->getPosition();
			if (shouldRender(position, cameraPos, screenWidth, screenHeight) == SDL_FALSE)
			{
				continue;
			}

			SDL_Texture *currentTexture = textureManager_.getTexture(*item->getTextureName());
			SDL_QueryTexture(currentTexture, nullptr, nullptr, &boundsRect.w, &boundsRect.h);
			SDL_RenderSetScale(this->windowRenderer_, item->getScale(boundsRect).x, item->getScale(boundsRect).y);
			boundsRect.x = (position.x * Globals::PIXELS_PER_METER + cameraPos.x - item->getSize().x / 2) / item->getScale(boundsRect).x;
			boundsRect.y = (screenHeight - position.y * Globals::PIXELS_PER_METER - item->getSize().y / 2 + cameraPos.y) / item->getScale(boundsRect).y;
			SDL_RenderCopy(this->windowRenderer_, currentTexture, nullptr, &boundsRect);
		}

		SDL_RenderPresent(this->windowRenderer_);
	}

	/*
	 * The camera works in the following manner:
	 * When going:
	 *	- up: y++
	 *  - down: y--
	 *  - left: x++ !
	 *  - right: x-- !
	*/
	SDL_bool Renderer::shouldRender(b2Vec2& renderablePosition, b2Vec2& cameraPosition, int& width, int& height)
	{
		SDL_Point point;
		point.x = renderablePosition.x * Globals::PIXELS_PER_METER;
		point.y = renderablePosition.y * Globals::PIXELS_PER_METER;
		SDL_Rect rect;
		rect.x = -cameraPosition.x;
		rect.y = cameraPosition.y;
		rect.h = height * 1.5;
		rect.w = width * 1.5;


		return SDL_PointInRect(&point, &rect);
	}
}