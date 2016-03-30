#include "Renderer.h"
#include <iostream>
#include "IRenderable.h">
#include "Globals\Constants.h"

namespace GameEngine 
{
	Renderer::Renderer(SDL_Window* window)
		: windowRenderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
		textureManager_(windowRenderer_),
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

	void Renderer::RenderAll()
	{
		SDL_RenderClear(this->windowRenderer_);
		SDL_Rect boundsRect;
		for (IRenderable *item : this->renderables_)
		{
			b2Vec2 position = item->getPosition();

			//1.6 meters character
			boundsRect.h = item->getHeight() * Globals::PIXELS_PER_METER;
			boundsRect.w = item->getWidth() * Globals::PIXELS_PER_METER;
			
			SDL_Texture *currentTexture = textureManager_.getTexture(item->getTextureName());
			SDL_RenderSetScale(this->windowRenderer_, item->getScale().x, item->getScale().y);
			boundsRect.x = position.x * Globals::PIXELS_PER_METER;
			boundsRect.y = worldConstraints.height - position.y * Globals::PIXELS_PER_METER - boundsRect.h;
			SDL_RenderCopy(this->windowRenderer_, currentTexture, NULL, &boundsRect);
		}

		SDL_RenderPresent(this->windowRenderer_);
	}
}